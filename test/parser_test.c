#include "lib_.h"
#include "parser.h"

int main() {
  char input[] = "  ls   -l  -a  ";
  char **tokens = parser(input);

  assert(strcmp_(tokens[0], "ls", 2) == 0 && tokens[0][2] == '\0');

  assert(strcmp_(tokens[1], "-l", 2) == 0 && tokens[1][2] == '\0');

  assert(strcmp_(tokens[2], "-a", 2) == 0 && tokens[2][2] == '\0');

  assert(tokens[3] == NULL);

  free_tokens(tokens);
  printf("parser(input) test passed\n");
  return EXIT_SUCCESS;
}
