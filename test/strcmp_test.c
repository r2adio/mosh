#include "lib_.h"

int main() {
  assert(strcmp_("abc", "abc", 3) == 0); // case 1: both strings are equal
  assert(strcmp_("abc", "def", 3) != 0); // case 2: s1 > s2
  assert(strcmp_("def", "abc", 3) != 0); // case 3: s2 > s1
  assert(strcmp_("abc", NULL, 3) != 0);  // case 4: s1 is not NULL, s2 is NULL

  printf("strcmp_(s1, s2, n) test passed\n");
  return EXIT_SUCCESS;
}
