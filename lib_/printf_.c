/**
 * agenda: make a function that prints a formatted string
 *
 * todo: [x] count the number of charactes in the string,
 *       [x] prints the one character
 *       [x] prints the complete stream (no formatted string)
 *       [x] take a char as an argument and converts it to a string
 *       [ ] print a formatted string
 */
#include "lib_.h"

// chardup_ returns a pointer to a new string that is a duplicate of the
// character c.
char *chardup_(const char c) {
  static char buf[2];
  char *p = buf;
  *p++ = c;
  *p = '\0';
  return buf;
}

// puts_ prints a string s to stdout
size_t puts_(char *s) {
  size_t n = strlen_(s);
  if (n < 1)
    return 0;

  return write(1, s, n);
}

int printf_(void) { return 0; }
