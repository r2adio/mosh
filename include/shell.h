#ifndef SHELL_H
#define SHELL_H

#include <errno.h> // for error handling, sets global variable for reporting system call errors: errno
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for POSIX operating system API (e.g., fork, exec)

#define MAX_INPUT 1024
char **parser(char *input);

#endif /* SHELL_H */
