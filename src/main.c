#include "builtin.h"
#include "parser.h"

static void event_loop(char **env) {
  char *input = NULL;    // storing input value
  size_t input_size = 0; // storing input size

  char **args = NULL;             // storing arguments
  char *init_dir = getenv("PWD"); // storing initial directory

  while (1) {
    fprintf(stdout, "ゝ"); // ctrl+k *5
    if (getline(&input, &input_size, stdin) == -1) {
      if (feof(stdin)) { // checks EOF, and breaks the loop
        putchar('\n');
        break;
      }
      perror("getline");
      break;
    }

    args = parser(input);

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
