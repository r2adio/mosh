#include "lib_.h"

int main() {
  assert(strcmp_("abc", "abc", 3) == 0);

  printf("strcmp_(s1, s2, n) test passed\n");
  return EXIT_SUCCESS;
}
