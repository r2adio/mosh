#include "shell.h"

int main() {
  char input[] = "  ls   -l  -a  ";
  char **tokens = parser(input);

  if (strcmp(tokens[0], "ls") != 0) {
    return EXIT_FAILURE;
  }
  if (strcmp(tokens[1], "-l") != 0) {
    return EXIT_FAILURE;
  }
  if (strcmp(tokens[2], "-a") != 0) {
    return EXIT_FAILURE;
  }
  if (tokens[3] != NULL) {
    return EXIT_FAILURE;
  }

  free_tokens(tokens);
  printf("Parser test passed\n");
  return EXIT_SUCCESS;
}
