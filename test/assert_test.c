#include "shell.h"
#include <assert.h>

int main(void) {
  char *test = NULL;
  assert(test != NULL);

  printf("Simple test passed\n");
  return EXIT_SUCCESS;
}
