#include "shell.h"

void event_loop(void) {
  char *input = NULL;    // storing input value
  size_t input_size = 0; // storing input size

  char **args; // storing arguments

  while (1) {
    printf("ゝ");                                    // ctrl+k *5
    if (getline(&input, &input_size, stdin) == -1) { // EOF, ctrl+d
      if (feof(stdin))                               // checks for EOF
        break;               // handles EOF gracefully, and exits the loop
      else if (errno != 0) { // checks for an actual error
        perror("getline");
        break;
      }
    }
    // printf("cmd: %s", input);

    args = parser(input);

    for (size_t i = 0; args[i]; i++) {
      printf("Args: %s\n", args[i]);
    }
  }
}

int main(void) {
  event_loop();
  return 0;
}
