#include "lib_.h"

/**
 * @param s1 first string
 * @param s2 second string
 * @param n number of characters to compare
 * @return 0 if equal, 1 if s1 > s2, -1 if s1 < s2
 */
int strcmp_(char *s1, char *s2, size_t n) {
  size_t i = 0;

  if (n == 0)
    return 0;
  while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i]) {
    i++;
  }
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
