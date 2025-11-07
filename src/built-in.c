#include "shell.h"

int builtin(char **args, char **env, char *init_dir) {
  // command: cd [dir_path]
  if (!strcmp(args[0], "cd")) {
    if (chdir(args[1]) == -1) {
      perror("cd");
      return 1;
    }
    printf("cd: %s\n", args[1]);

    // command: pwd
  } else if (!strcmp(args[0], "pwd")) {
    if (chdir(init_dir) == -1) {
      perror("chdir");
      return 1;
    }
    printf("pwd: %s\n", init_dir);

    // command: exit
  } else if (!strcmp(args[0], "exit")) {
    exit(EXIT_SUCCESS);

    // not  a builtin command
  } else {
    printf("not a builtin command\n");
  }
  return 0;
}
