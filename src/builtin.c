#include "builtin.h"
#include "lib_.h"
#include <string.h>

// built-in: cd pwd exit echo alias source which type env setenv unsetenv
int builtin(char **args, char **env, char *init_dir) {
  if (!strcmp_(args[0], "cd", 2) && args[0][2] == '\0') {
    return cd_cmd(args, init_dir);

  } else if (!strcmp_(args[0], "pwd", 3) && args[0][3] == '\0') {
    return pwd_cmd(args);

  } else if (!strcmp_(args[0], "echo", 4) && args[0][4] == '\0') {
    return echo_cmd(args, env);

  } else if (!strcmp_(args[0], "env", 3) && args[0][3] == '\0') {
    return env_cmd(env);

  } else if (!strcmp_(args[0], "which", 5) && args[0][5] == '\0') {
    return which_cmd(args, env);

  } else if (!strcmp_(args[0], "exit", 4) && args[0][4] == '\0') {
    exit(EXIT_SUCCESS);

  } else {
    printf("mosh: command not found: %s\n", args[0]);
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

int pwd_cmd(char **args) {
  if (args[1]) {
    printf("pwd: too many arguments\n");
    return EXIT_FAILURE;
  }
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
        printf("%s ", getenv_(args[i] + 1, env));
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

int which_cmd(char **args, char **env) {
  if (!args[1]) {
    printf("which: expected arguments\n");
  }
  static const char *builtins[] = {"cd",    "pwd",    "exit",     "echo",
                                   "alias", "source", "which",    "type",
                                   "env",   "setenv", "unsetenv", NULL};
  for (uint8_t i = 0; builtins[i]; i++) {
    if (!strcmp_(args[1], builtins[i], strlen_(builtins[i]))) {
      printf("%s: shell built-in command\n", builtins[i]);
      return EXIT_SUCCESS;
    }
  }

  // not a built-in command
  static char *path_env = NULL;  // stores PATH value
  static char *path_temp = NULL; // duplicate of PATH
  static char *token = NULL;     // tokenizes dir's PATH
  static char path[MAX_INPUT];   // stores the full PATH

  path_env = getenv_("PATH", env);
  if (!path_env) {
    perror("getenv_");
    return EXIT_FAILURE;
  }

  path_temp = strdup(path_env); // duplicates the PATH
  if (!path_temp) {
    perror("strdup");
    free(path_env);
    return EXIT_FAILURE;
  }

  // tokenizes PATH into individual dirs {`:` -> delimiter}
  token = strtok(path_temp, ":"); // strtok: doesnt allocate memory for `token`
  // `token` points to the memory block pointed by `path_temp`
  while (token) {
    snprintf(path, sizeof(path), "%s/%s", token,
             args[1]);             // concatenates the command's path
    if (access(path, X_OK) == 0) { // access: checks if file exists
      printf("%s\n", path);        // prints the command's path
      free(path_temp);
      free(path_env);
      return EXIT_SUCCESS;
    }
    token = strtok(NULL, ":");
  }
  printf("%s not found\n", args[1]);

  free(path_temp);
  free(path_env);
  return EXIT_SUCCESS;
}
