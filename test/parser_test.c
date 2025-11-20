#include "lib_.h"
#include "parser.h"

int main() {
  char input[] = "  ls   -l  -a  ";
  char **tokens = parser(input);

  if (strcmp_(tokens[0], "ls", 2) != 0) {
    return EXIT_FAILURE;
  }
  if (strcmp_(tokens[1], "-l", 2) != 0) {
    return EXIT_FAILURE;
  }
  if (strcmp_(tokens[2], "-a", 2) != 0) {
    return EXIT_FAILURE;
  }
  if (tokens[3] != NULL) {
    return EXIT_FAILURE;
  }

  free_tokens(tokens);
  printf("Parser test passed\n");
  return EXIT_SUCCESS;
}
