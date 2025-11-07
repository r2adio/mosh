#include "shell.h"

// built-in: cd pwd exit echo alias source which type env setenv unsetenv
int cd_cmd(char **args, char *init_dir) {
  if (chdir(args[1]) == -1) {
    perror("cd");
    return EXIT_FAILURE;
  }
  printf("cd: %s\n", args[1]);
  return EXIT_SUCCESS;
}

int pwd_cmd() {
  char *cwd = getcwd(NULL, 0);
  if (cwd == NULL) {
    perror("pwd");
    return EXIT_FAILURE;
  }
  printf("pwd: %s\n", cwd); // print current working directory
  return EXIT_SUCCESS;
}

int echo_cmd(char **args, char **env);

int env_cmd(char **env);

int which_cmd(char **args, char **env);
