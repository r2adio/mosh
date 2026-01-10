#include "builtin.h"
#include "colors.h"
#include "parser.h"

int main() {
  char **env = NULL;
  char *init_dir = NULL;

  // TEST: token parser
  char input[] = "cd /usr/local/bin/";
  char **tokens = parser(input);
  assert(strcmp(tokens[1], "/usr/local/bin/") == 0);

  // TEST: builtin and cd command
  int cd_res = builtin(tokens, env, init_dir);
  assert(cd_res == EXIT_SUCCESS);
  free_tokens(tokens);

  // TEST: pwd command
  char input_pwd[] = "pwd";
  tokens = parser(input_pwd);
  int res = builtin(tokens, env, init_dir);
  assert(res == EXIT_SUCCESS);

  // TEST: cwd is /usr/local/bin
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  printf("cwd: %s\n", cwd);
  assert(strstr(cwd, "/usr/local/bin") != NULL);

  free_tokens(tokens);
  fprintf(
      stdout, GREEN
      "builtin(char **args, char **env, char *init_dir) test passed\n" RESET);
  return EXIT_SUCCESS;
}
