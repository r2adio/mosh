#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char buf[1024];
  fputs("% ", stdout);
  fflush(stdout);

  if (fgets(buf, sizeof(buf), stdin) == NULL) exit(1); // ctrl-d (eof)

  char *nl = strchr(buf, '\n'); // trims \n char
  if (nl) *nl = '\0';

  pid_t pid = fork();
  if (pid < 0) err(EXIT_FAILURE, "fork"); // no child
  if (pid > 0) wait(NULL);                // parent: wait for child process
  else {                                  // child: pid == 0
    execlp(buf, buf, NULL);               // replace child with prog
    err(EXIT_FAILURE, "execlp");          // execlp() fails
  }
  return EXIT_SUCCESS;
}
