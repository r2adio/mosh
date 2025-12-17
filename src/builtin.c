#include "builtin.h"
#include "lib_.h"
#include <string.h>

typedef int (*builtin_fn)(char **args, char **env, char *init_dir);

typedef struct {
  const char *name;
  builtin_fn fn; // int (*fn)(char **, char **, char *);
} builtin_t;

builtin_t builtins[] = {
    {"cd", cd_cmd},   {"pwd", pwd_cmd},     {"echo", echo_cmd},
    {"env", env_cmd}, {"which", which_cmd}, {"exit", exit_cmd},
};

int builtin(char **args, char **env, char *init_dir) {
  for (size_t i = 0; i < BUILTIN_COUNT; i++) {
    if (strcmp(args[0], builtins[i].name) == 0) {

      if (strcmp(args[0], "exit") == 0)
        exit(EXIT_SUCCESS);

      return builtins[i].fn(args, env, init_dir);
    }
  }

  printf("mosh: command not found: %s\n", args[0]);
  return EXIT_SUCCESS;
}

// TODO: cd, cd ~
int cd_cmd(char **args, char **env, char *init_dir) {
  (void)env;
  (void)init_dir;
  if (chdir(args[1]) == -1) { // change wd
    perror("cd");
    return EXIT_FAILURE;
  }
  printf("cd: %s\n", args[1]);
  return EXIT_SUCCESS;
}

int pwd_cmd(char **args, char **env, char *init_dir) {
  (void)env;
  (void)init_dir;
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

int echo_cmd(char **args, char **env, char *init_dir) {
  (void)env;
  (void)init_dir;
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

int env_cmd(char **args, char **env, char *init_dir) {
  (void)args;
  (void)init_dir;
  size_t i = 0;
  while (env[i]) {
    printf("%s\n", env[i]);
    i++;
  }
  return EXIT_SUCCESS;
}

int which_cmd(char **args, char **env, char *init_dir) {
  (void)init_dir;
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
  char *path_env = getenv_("PATH", env); // stores PATH value
  if (!path_env) {
    perror("getenv_");
    return EXIT_FAILURE;
  }

  char *path_temp = strdup(path_env); // duplicates the PATH
  if (!path_temp) {
    perror("strdup");
    return EXIT_FAILURE;
  }

  char path[MAX_INPUT]; // stores the full PATH

  // tokenizes PATH into individual dirs {`:` -> delimiter}
  char *token =
      strtok(path_temp, ":"); // strtok: doesnt allocate memory for `token`
  // `token` points to the memory block pointed by `path_temp`
  while (token) {
    snprintf(path, sizeof(path), "%s/%s", token,
             args[1]);             // concatenates the command's path
    if (access(path, X_OK) == 0) { // access: checks if file exists
      printf("%s\n", path);        // prints the command's path
      free(path_temp);
      return EXIT_SUCCESS;
    }
    token = strtok(NULL, ":");
  }
  printf("%s not found\n", args[1]);

  free(path_temp);
  return EXIT_SUCCESS;
}

int exit_cmd(char **args, char **env, char *init_dir) {
  (void)args;
  (void)env;
  (void)init_dir;
  exit(EXIT_SUCCESS);
}
