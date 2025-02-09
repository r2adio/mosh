#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
//access(), check file execution permisions
#include <vector>
//manages buil-in cmds dynamically
#include <sstream>
//useful for handling input parsing

std::vector <std::string> builtins = {"echo", "exit", "type"};

bool is_builtin(const std::string &cmd) {
  for(const std::string &builtin : builtins){
    if (cmd == builtin)
      return true;
  }
  return false;
}

std::string find_in_path(const std::string &cmd) {
  char *path = getenv("PATH");
  if (!path)
    return "";

  char *dup_path = strdup(path); // Duplicate PATH to avoid modifying the original
  char *token = strtok(dup_path, ":");

  while (token) {
    std::string full_path = std::string(token) + "/" + cmd;
    if (access(full_path.c_str(), X_OK) == 0) {
      free(dup_path);
      return full_path;
    }
    token = strtok(nullptr, ":");
  }

  free(dup_path);
  return "";
}

void shell_type(const std::string &cmd) {
  if (cmd.empty()) {
    std::cout << "type: missing argument\n";
    return;
  }
  
  if (is_builtin(cmd)) 
    std::cout << cmd << " is a shell builtin\n";

  else {
    std::string path = find_in_path(cmd);
    if (!path.empty())
      std::cout << cmd << " is " << path << "\n";
    else
      std::cout << cmd << ": not found\n";
  }
}

//checks if string is valid integer
bool is_int(const std::string &str) {
  if(str.empty())
    return false;
  for(char ch : str) {
    if(!std::isdigit(ch))
      return false;
  }
  return true;
}
//function to process exit cmd
void handle_exit(const std::string &arg) {
  if(arg.empty())
    std::cout<< "exit requires atleast one argument to exit shell\n";
  else if(is_int(arg)) {
    int exit_code = std::stoi(arg);
    std::cout<< "exiting the code "<< exit_code<< '\n';
    std::exit(exit_code);
  }
  else
    std::cout<< "exit code must be an integer\n";
}

int main() {
  // enables or diables automatic flushing of the output stream after any output operation, std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";
  std::string input;
  
  while (std::getline(std::cin, input)) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while(iss>> token) {
      tokens.push_back(token);
    }
    if(tokens.empty()) {
      std::cout<< "$ ";
      continue;
    }
    if(tokens[0] == "exit") {
      std::string arg = (tokens.size() >1) ? tokens[1] : "";
      handle_exit(arg);
    }
    else
      std::cout<< tokens[0]<< ": command not found\n";

    std::cout<< "$ ";
  }
  return 0;
}
