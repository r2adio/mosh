#include "shell.h"

int builtin(char **args, char **env, char *init_dir) {
  printf("builtin: %s\n", args[0]);
  if (!strcmp(args[0], "cd")) {
    if (chdir(args[1]) == -1) {
      perror("chdir");
      return 1;
    } else {
      printf("cd: %s\n", args[1]);
    }
  } else if (!strcmp(args[0], "pwd")) {
    if (chdir(init_dir) == -1) {
      perror("chdir");
      return 1;
    }
    printf("pwd: %s\n", init_dir);
  } else if (!strcmp(args[0], "exit")) {
    exit(EXIT_SUCCESS);
  } else { // not  a builtin command
    printf("not a builtin command\n");
  }
  return 0;
}
