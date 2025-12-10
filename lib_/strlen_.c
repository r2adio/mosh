#include "lib_.h"

/**
 * @param s string
 * @return length of string
 */
size_t strlen_(const char *s) {
  // check for either pointer being NULL, preventing a segmentation fault
  if (!s)
    return 0;

  size_t i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}
