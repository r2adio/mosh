#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

const char *builtins[] = {"echo", "exit", "type", nullptr};

bool is_builtin(const std::string &cmd) {
    for (int i = 0; builtins[i]; i++) {
        if (cmd == builtins[i]) {
            return true;
        }
    }
    return false;
}

std::string find_in_path(const std::string &cmd) {
    char *path = getenv("PATH");
    if (!path) return "";

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
    
    if (is_builtin(cmd)) {
        std::cout << cmd << " is a shell builtin\n";
    } else {
        std::string path = find_in_path(cmd);
        if (!path.empty()) {
            std::cout << cmd << " is " << path << "\n";
        } else {
            std::cout << cmd << ": not found\n";
        }
    }
}

int main() {
  // enables or diables automatic flushing of the output stream after any output operation, std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";
  std::string input;

  while (std::getline(std::cin, input) && input.find("exit") != 0) {
    if (input.find("echo ") == 0) {
      const int echo_len = 5;
      std::string text = input.substr(echo_len);
      std::cout << text << '\n';
    }
    else if (input.find("type ") == 0) {
      std::string cmd = input.substr(5);
      shell_type(cmd);
    }
    else
      std::cout << input << ": command not found\n";
    std::cout << "$ ";
  }
}

