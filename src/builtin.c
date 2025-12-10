#include "builtin.h"
#include "lib_.h"

// built-in: cd pwd exit echo alias source which type env setenv unsetenv
int builtin(char **args, char **env, char *init_dir) {
  if (!strcmp_(args[0], "cd", 2) && args[0][2] == '\0') {
    return cd_cmd(args, init_dir);

  } else if (!strcmp_(args[0], "pwd", 3) && args[0][3] == '\0') {
    return pwd_cmd();

  } else if (!strcmp_(args[0], "echo", 4) && args[0][4] == '\0') {
    return echo_cmd(args, env);

  } else if (!strcmp_(args[0], "env", 3) && args[0][3] == '\0') {
    return env_cmd(env);

  } else if (!strcmp_(args[0], "exit", 4) && args[0][4] == '\0') {
    exit(EXIT_SUCCESS);

  } else {
    // binary: ls grep find cat cp mv rm mkdir tar
  }
  return EXIT_SUCCESS;
}

// built-in: cd pwd exit echo alias source which type env setenv unsetenv

// TODO: cd, cd ~
int cd_cmd(char **args, char *init_dir) {
  (void)init_dir;
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
  (void)env;
  if (args[1] && !strcmp_(args[1], "-n", 2) && args[1][2] == '\0') {
    for (size_t i = 2; args[i]; i++) {
      printf("%s ", args[i]);
    }
    return EXIT_SUCCESS;
  } else {
    for (size_t i = 1; args[i]; i++) {
      if (args[i][0] == '$') { // checks env vars
        printf("%s ", getenv(args[i] + 1));
      } else if (args[i][0] == '"' &&
                 args[i][strlen_(args[i]) - 1] == '"') { // checks for quotes
        size_t len = strlen_(args[i]);
        if (len >= 2) {
          printf("%.*s ", (int)(len - 2), args[i] + 1);
        }
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
