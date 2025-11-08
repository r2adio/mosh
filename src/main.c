#include "shell.h"

// built-in: cd pwd exit echo alias source which type env setenv unsetenv
int builtin(char **args, char **env, char *init_dir) {
  if (!strcmp(args[0], "cd")) {
    return cd_cmd(args, init_dir);

  } else if (!strcmp(args[0], "pwd")) {
    return pwd_cmd();

  } else if (!strcmp(args[0], "echo")) {
    return echo_cmd(args, env);

  } else if (!strcmp(args[0], "env")) {
    return env_cmd(env);

  } else if (!strcmp(args[0], "exit")) {
    exit(EXIT_SUCCESS);

  } else {
    // binary: ls grep find cat cp mv rm mkdir tar
  }
  return EXIT_SUCCESS;
}

void event_loop(char **env) {
  char *input = NULL;    // storing input value
  size_t input_size = 0; // storing input size

  char **args;                    // storing arguments
  char *init_dir = getenv("PWD"); // storing initial directory

  while (1) {
    printf("ゝ");                                    // ctrl+k *5
    if (getline(&input, &input_size, stdin) == -1) { // EOF, ctrl+dmain
      if (feof(stdin))                               // checks for EOF
        break;               // handles EOF gracefully, and exits the loop
      else if (errno != 0) { // checks for an actual error
        perror("getline");
        break;
      }
    }
    // printf("cmd: %s", input);

    args = parser(input);

    // for (size_t i = 0; args[i]; i++) {
    //   printf("Args: %s\n", args[i]);
    // }

    if (args[0] != NULL) {
      builtin(args, env, init_dir);
    }
  }
  free_tokens(args); // free allocated memory for tokens
}

/* The `env` parameter holds the environment variables passed from the parent
 * process. It is essential for a shell's functionality, such as locating
 * executables in the PATH, expanding variables, and passing the environment
 * to child processes.
 */
int main(int argc, char **argv, char **env) {
  (void)argc;
  (void)argv;
  event_loop(env);
  return EXIT_SUCCESS;
}
