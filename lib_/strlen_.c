#include "lib_.h"

/**
 * @param s string
 * @return length of string
 */
size_t strlen_(char *s) {
  size_t i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}
