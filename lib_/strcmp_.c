#include "lib_.h"

/**
 * @param s1 first string
 * @param s2 second string
 * @param n number of characters to compare
 * @return 0 if equal within n characters, otherwise the diff between
 *         the first differing characters (as unsigned char values)
 */
int strcmp_(const char *s1, const char *s2, size_t n) {
  // check for either pointer being NULL, preventing a segmentation fault
  if (!s1 || !s2)
    return s1 == s2 ? 0 : (s1 ? 1 : -1);

  size_t i = 0;

  if (n == 0)
    return 0;

  while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
    i++;
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
