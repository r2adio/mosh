#include "utils.h"

/**
 * @brief Get the value of an environment variable
 *
 * @param name The name of the environment variable
 * @param env The environment variables
 * @return The value of the environment variable, or NULL if not found
 */
char *getenv_(const char *name, char **env) {
  if (name == NULL || env == NULL)
    return NULL;

  size_t name_len = strlen(name);
  for (size_t i = 0; env[i]; i++) {
    if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
      return &env[i][name_len + 1];
  }
  return NULL;
}
