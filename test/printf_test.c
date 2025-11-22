#include "lib_.h"

int main(void) {
  puts_("hello world\n");

  char *p = chardup_('X');
  puts_(p);

  putchar_('X');
  return EXIT_SUCCESS;
}
