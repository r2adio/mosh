#include "unity.h"

#include "builtin.h"
#include "parser.h"

void setUp(void) {
}
void tearDown(void) {
}

static void test_parser_splits_cd_command(void) {
  char input[] = "cd /usr/local/bin/";
  char **tokens = parser(input);

  TEST_ASSERT_NOT_NULL(tokens);
  TEST_ASSERT_NOT_NULL(tokens[0]);
  TEST_ASSERT_NOT_NULL(tokens[1]);
  TEST_ASSERT_EQUAL_STRING("cd", tokens[0]);
  TEST_ASSERT_EQUAL_STRING("/usr/local/bin/", tokens[1]);

  free_tokens(tokens);
}

static void test_builtin_cd_and_pwd(void) {
  char **env = NULL;
  char *init_dir = NULL;
  char input[] = "cd /usr/local/bin/";
  char **tokens = parser(input);

  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, builtin(tokens, env, init_dir));
  free_tokens(tokens);

  char input_pwd[] = "pwd";
  tokens = parser(input_pwd);
  TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, builtin(tokens, env, init_dir));

  char cwd[PATH_MAX];
  TEST_ASSERT_NOT_NULL(getcwd(cwd, sizeof(cwd)));
  TEST_ASSERT_NOT_NULL(strstr(cwd, "/usr/local/bin"));

  free_tokens(tokens);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_parser_splits_cd_command);
  RUN_TEST(test_builtin_cd_and_pwd);
  return UNITY_END();
}
