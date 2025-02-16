#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
// access(), check file execution permisions
#include <vector>
// manages buil-in cmds dynamically
#include <sstream>
// useful for handling input parsing
#include <filesystem>

std::vector<std::string> builtins = {"echo", "exit", "type"};

bool is_builtin(const std::string &cmd) {
  for (const std::string &builtin : builtins) {
    if (cmd == builtin)
      return true;
  }
  return false;
}

std::string find_in_path(const std::string &cmd) {
  const char *path = getenv("PATH");
  if (!path)
    return "";

  std::istringstream stream(path);
  std::string directory;

  while (std::getline(stream, directory, ':')) {
    std::filesystem::path full_path = std::filesystem::path(directory) / cmd;
    if (std::filesystem::exists(full_path) &&
        std::filesystem::is_regular_file(full_path)) {
      return full_path.string();
    }
  }
  return "";
}

void shell_type(const std::string &cmd) {
  if (cmd.empty()) {
    std::cout << "type: missing argument\n";
    return;
  }

  if (is_builtin(cmd))
    std::cout << cmd << " is a shell builtin\n";

  std::string path = find_in_path(cmd);
  if (!path.empty())
    std::cout << cmd << " is " << path << "\n";
  else
    std::cout << cmd << ": not found\n";
}

// checks if string is valid integer
bool is_int(const std::string &str) {
  try {
    size_t pos;
    std::stoi(str, &pos);
    return pos == str.size(); // ensure entire string is parsed
  } catch (...) {
    return false;
  }
}
// function to process exit cmd
void handle_exit(const std::vector<std::string> &tokens) {
  if (tokens.size() == 1) {
    std::cout << "Exiting with code 0\n";
    std::exit(0);
  } 
  else if (tokens.size() == 2 && is_int(tokens[1])) {
    int exit_code = std::stoi(tokens[1]);
    std::cout << "Exiting with code " << exit_code << "\n";
    std::exit(exit_code);
  } 
  else
    std::cout << "exit: argument must be an integer\n";
}

//helps input to divide into separate tokens
std::vector<std::string> tokensize(const std::string &input) {
  std::istringstream splits(input);  //istringstream splits on spaces
  std::vector<std::string> tokens;
  std::string token;

  while (splits >> token) {  // reads words one by one
    tokens.push_back(token);
  }
  return tokens;
}

int main() {
  // enables or diables automatic flushing of the output stream after any output
  // operation, std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";
  std::string input;

  while (std::getline(std::cin, input)) {
    std::vector<std::string> tokens = tokensize(input);

    if (tokens.empty()) {
      std::cout << "$ ";
      continue;
    }

    // always takes first wrd as command
    std::string command = tokens[0];
    // Handle built-in 'exit'
    if (command == "exit") {
      handle_exit(tokens);
    }
    // Handle built-in 'echo'
    else if (command == "echo") {
      for (size_t i = 1; i < tokens.size(); i++) {
        std::cout << tokens[i] << " ";
      }
      std::cout << std::endl;
    }
    // Handle built-in 'type'
    else if (command == "type") {
      if (tokens.size() > 1) {
        shell_type(tokens[1]); // Pass the second argument to type command
      } else {
        std::cout << "type: missing argument\n";
      }
    }
    // If not a built-in, print "command not found"
    else {
      std::cout << command << ": cmd not found\n";
    }

    std::cout << "$ ";
  }

  return 0;
}
