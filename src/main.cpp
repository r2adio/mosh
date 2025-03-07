#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

enum CommandType {
  Builtin,     // internal command of shell
  Executable,  // external programs
  Nonexistent, // zzz
};

struct FullCommandType {
  CommandType type;
  std::string executable_path; // path to executable
};

std::vector<std::string> parse_command_to_string_vector(std::string command);
FullCommandType command_to_full_command_type(std::string command);
std::string find_command_executable_path(std::string command);
std::string find_command_in_path(std::string command, std::string path);

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);

    // parsing the user input
    std::vector<std::string> command_vector =
        parse_command_to_string_vector(input);

    if (command_vector.size() == 0) {
      continue;
    }

    //classifies the command into builtin, executable,nonexistent
    FullCommandType fct = command_to_full_command_type(command_vector[0]);

    // handle builtin commands
    if (fct.type == Builtin) {
      if (command_vector[0] == "exit") {
        int exit_code = std::stoi(command_vector[1]);
        return exit_code;
      }

      if (command_vector[0] == "echo") {
        for (int i = 1; i < command_vector.size(); i++) {
          // print a space before every item that is not the first
          if (i != 1) {
            std::cout << " ";
          }

          std::cout << command_vector[i];
        }

        std::cout << "\n";
        continue;
      }

      if (command_vector[0] == "type") {
        if (command_vector.size() < 2) {
          continue;
        }

        std::string command_name = command_vector[1];
        FullCommandType command_type =
            command_to_full_command_type(command_name);

        switch (command_type.type) {
        case Builtin:
          std::cout << command_name << " is a shell builtin\n";
          break;
        case Executable:
          std::cout << command_name << " is " << command_type.executable_path
                    << "\n";
          break;
        case Nonexistent:
          std::cout << command_name << " not found\n";
          break;
        default:
          break;
        }

        continue;
      }

      continue;
    }

    if (fct.type == Executable) {
      // Extract just the filename for the first argument
      std::string executable_name =
          std::filesystem::path(fct.executable_path).filename();

      // Use execv instead of system, which gives more control over the
      // arguments
      std::vector<char *> args;
      args.push_back(const_cast<char *>(
          executable_name.c_str())); // Program name as first arg

      // Add remaining arguments
      for (int argn = 1; argn < command_vector.size(); argn++) {
        args.push_back(const_cast<char *>(command_vector[argn].c_str()));
      }
      args.push_back(nullptr); // Null-terminate the args array

      // Fork and execute
      pid_t pid = fork();
      if (pid == 0) {
        // Child process
        execv(fct.executable_path.c_str(), args.data());
        // If execv returns, there was an error
        perror("execv");
        exit(1);
      } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
      } else {
        // Fork failed
        perror("fork");
      }

      continue;
    }

    std::cout << input << ": command not found\n";
  }
}

std::vector<std::string> parse_command_to_string_vector(std::string command) {
  std::vector<std::string> args;
  std::string arg_acc = "";

  for (char c : command) {
    if (c == ' ') {
      args.push_back(arg_acc);
      arg_acc = "";
    } else {
      arg_acc += c;
    }
  }

  if (arg_acc != "") {
    args.push_back(arg_acc);
  }

  return args;
}

// returns the full command type of a command (without arguments)
FullCommandType command_to_full_command_type(std::string command) {
  std::vector<std::string> builtin_commands = {"exit", "echo", "type"};

  // checks if builtin command
  if (std::find(builtin_commands.begin(), builtin_commands.end(), command) !=
      builtin_commands.end()) {
    FullCommandType fct;
    fct.type = CommandType::Builtin;

    return fct;
  }

  // check if the command is found in path
  std::string exec_path = find_command_executable_path(command);
  if (exec_path != "") {
    FullCommandType fct;
    fct.type = Executable;
    fct.executable_path =
        exec_path; // Store the full path instead of just the filename
    return fct;
  }

  // nonexistent types
  FullCommandType fct;
  fct.type = CommandType::Nonexistent;
  return fct;
}

std::string find_command_executable_path(std::string command) {
  char *path = getenv("PATH");

  if (path == NULL) {
    return "";
  }

  std::string path_acc = "";

  // accumulate values in path_acc
  // and search whenever the directory is complete
  char *p = path;
  while (*p != '\0') {
    // search for end of paths
    if (*p == ':') {
      std::string exec_path = find_command_in_path(command, path_acc);

      if (exec_path != "") {
        return exec_path;
      }

      path_acc = "";
    } else {
      path_acc += *p;
    }
    p++;
  }

  // handle the last path in the string
  std::string exec_path = find_command_in_path(command, path_acc);

  if (exec_path != "") {
    return exec_path;
  }

  return "";
}

//std::string find_command_in_path(std::string command, std::string path) {
//  for (const auto &entry : std::filesystem::directory_iterator(path)) {
//    if (entry.path() == (path + "/" + command)) {
//      // Check if the file is executable
//      if (access(entry.path().c_str(), X_OK) == 0) {
//        return entry.path();
//      }
//    }
//  }
//  return "";
//}
std::string find_command_in_path(std::string command, std::string path) {
    // Check if the directory exists before trying to iterate
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        return "";
    }
    
    try {
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path() == (path + "/" + command)) {
                // Check if the file is executable
                if (access(entry.path().c_str(), X_OK) == 0) {
                    return entry.path();
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        // Handle filesystem errors gracefully
        std::cerr << "Warning: Could not search path: " << path << " (" << e.what() << ")\n";
    }
    
    return "";
}
