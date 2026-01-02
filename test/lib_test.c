#include "lib_.h"

int main() {
  // strcmp_
  assert(strcmp_("abc", "abc", 3) == 0); // case 1: both s1 and s2 are equal
  assert(strcmp_("abc", "def", 3) < 0);  // case 2: s1 < s2
  assert(strcmp_("def", "abc", 3) > 0);  // case 3: s1 > s2
  assert(strcmp_("abc", NULL, 3) != 0);  // case 4: s1 is not NULL, s2 is NULL
  printf("strcmp_(const char *s1, const char *s2, size_t n) test passed\n");

  // strlen_
  char *s = "abc";
  assert(strlen_(s) == 3);
  assert(strlen_(NULL) == 0);
  printf("strlen(const char *s) test passed\n");

  return EXIT_SUCCESS;
}
