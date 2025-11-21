#include "lib_.h"

/**
 * @param s string
 * @return length of string
 */
int strlen_(char *s) {
  size_t i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}
