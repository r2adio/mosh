#include "lib_.h"

char *getenv_(const char *name, char **env) {
  if (name == NULL || env == NULL)
    return NULL;

  size_t name_len = strlen_(name);
  for (size_t i = 0; env[i]; i++) {
    if (strcmp_(env[i], name, name_len) == 0 && env[i][name_len] == '=')
      return &env[i][name_len + 1];
  }

  return NULL;
}
