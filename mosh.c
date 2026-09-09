#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  while (1) {
    char buf[1024];
    fputs("% ", stdout);
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) == NULL) break; // ctrl-d (eof)

    char *nl = strchr(buf, '\n'); // trims \n char
    if (nl) *nl = '\0';

    // tokenization
    char *args[20];
    int nargs = 0;
    args[nargs] = strtok(buf, " ");
    while (args[nargs] != NULL) args[++nargs] = strtok(NULL, "");

    if (args[0] == NULL) continue; // avoid seg fault with empty input
    if (strcmp(args[0], "exit") == 0) exit(0);

    pid_t pid = fork();
    if (pid < 0) err(EXIT_FAILURE, "fork"); // no child
    if (pid > 0) wait(NULL);                // parent: wait for child process
    else {                                  // child: pid == 0
      execvp(args[0], args);                // replace child with prog
      err(EXIT_FAILURE, "execlp");          // execlp() fails
    }
  }
  return EXIT_SUCCESS;
}
