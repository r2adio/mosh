#include "shell.h"

void event_loop(char **env) {
  char *input = NULL;    // storing input value
  size_t input_size = 0; // storing input size

  char **args; // storing arguments

  while (1) {
    printf("ゝ");                                    // ctrl+k *5
    if (getline(&input, &input_size, stdin) == -1) { // EOF, ctrl+d
      if (feof(stdin))                               // checks for EOF
        break;               // handles EOF gracefully, and exits the loop
      else if (errno != 0) { // checks for an actual error
        perror("getline");
        break;
      }
    }
    // printf("cmd: %s", input);

    args = parser(input);

    for (size_t i = 0; args[i]; i++) {
      printf("Args: %s\n", args[i]);
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
  return 0;
}
