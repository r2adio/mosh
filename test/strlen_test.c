#include "lib_.h"
#include <stdio.h>

int main(void) {
  char *s = "abc";
  assert(strlen_(s) == 3);
  assert(strlen_(NULL) == 0);

  printf("strlen(s) test passed\n");
  return EXIT_SUCCESS;
}
