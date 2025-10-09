#ifndef SHELL_H
#define SHELL_H

#include <errno.h> // for error handling, sets global variable for reporting system call errors: errno
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for POSIX operating system API (e.g., fork, exec)

#define MAX_INPUT 1024

char **parser(char *input);
void free_tokens(char **tokens);
int builtin(char **args, char **env, char *init_dir);

#endif /* SHELL_H */
