#include "builtin.h"
#include "parser.h"

int main() {
  char **env = NULL;
  char *init_dir = NULL;
  char input[] = "cd src/";
  char **tokens = parser(input);

  assert(builtin(tokens, env, init_dir) != EXIT_FAILURE);

  free_tokens(tokens);
  printf("builtin(tokens, env, init_dir) test passed\n");
  return EXIT_SUCCESS;
}
