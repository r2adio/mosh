#include "shell.h"

// parse user input into tokens
char **parser(char *input) {
  size_t buf_size = MAX_INPUT; // buffer size: 1024
  char **tokens =
      malloc(buf_size * sizeof(char *)); // allocate memory for tokens
  char *token = NULL;                    // token
  size_t position = 0;                   // position in tokens
  size_t token_len = 0;                  // token length

  // check for malloc errors
  if (!tokens) {
    perror("Malloc");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; input[i]; i++) {
    token = &input[i];
    // input[i] && input[i] != ' ' -> ??
    // in c, every char is also an integer value.
    // the null character(\0), which marks the end of a string, has a value of 0
    // and, any other character has a non-zero value.
    //
    // thus, first check is for null terminator(\0), the end of a string,
    // and second checks if the character at the current position is not a ' '.
    while (input[i] && input[i] != ' ') {
      token_len++;
      i++;
    }

    // allocate memory for token
    tokens[position] = malloc((token_len + 1) * sizeof(char));
    if (!tokens[position]) {
      perror("Malloc");
      exit(EXIT_FAILURE);
    }

    // copy token to tokens array and add null terminator to token
    for (size_t j = 0; j < token_len; j++) {
      tokens[position][j] = token[j];
    }
    tokens[position][token_len] = '\0'; // null terminator at the end of token
    position++;
    token_len = 0; // reset token length
  }
  tokens[position] = NULL; // null terminator at the end of tokens array

  return tokens;
}

// free the allocated memory for tokens
void free_tokens(char **tokens) {
  if (tokens) // check if tokens is not null
    return;

  for (size_t i = 0; tokens[i]; i++) {
    free(tokens[i]); // free memory for each token
  }
  free(tokens); // free memory for tokens array
}
