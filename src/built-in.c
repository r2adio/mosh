#include "shell.h"
#include <stddef.h>

// built-in: cd pwd exit echo alias source which type env setenv unsetenv

// TODO: cd, cd ~
int cd_cmd(char **args, char *init_dir) {
  if (chdir(args[1]) == -1) { // change wd
    perror("cd");
    return EXIT_FAILURE;
  }
  printf("cd: %s\n", args[1]);
  return EXIT_SUCCESS;
}

int pwd_cmd(void) {
  char *cwd = getcwd(NULL, 0); // use dynamic memory allocation
  if (cwd == NULL) {
    perror("pwd");
    return EXIT_FAILURE;
  }
  printf("pwd: %s\n", cwd); // print current working directory
  free(cwd);
  return EXIT_SUCCESS;
}

int echo_cmd(char **args, char **env) {
  if (args[1] != NULL && !strcmp(args[1], "-n")) { // checks for -n flag
    for (size_t i = 2; args[i]; i++) {
      printf("%s ", args[i]);
    }
    return EXIT_SUCCESS;
  } else {
    for (size_t i = 1; args[i]; i++) {
      if (args[i][0] == '$') { // checks env vars
        printf("%s ", getenv(args[i] + 1));
      } else if (args[i][0] == '"' &&
                 args[i][strlen(args[i]) - 1] == '"') { // checks for quotes
        printf("%s ", args[i] + 1); // FIX: doesn't rm closing quote
      } else {
        printf("%s ", args[i]);
      }
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}

int env_cmd(char **env) {
  size_t i = 0;
  while (env[i]) {
    printf("%s\n", env[i]);
    i++;
  }
  return EXIT_SUCCESS;
}

int which_cmd(char **args, char **env);
