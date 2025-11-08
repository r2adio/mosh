#ifndef SHELL_H
#define SHELL_H

#include <errno.h> // for error handling, sets global variable for reporting system call errors: errno
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for POSIX operating system API (e.g., fork, exec)

char **parser(char *input);
void free_tokens(char **tokens);
int builtin(char **args, char **env, char *init_dir);

// built-in commands:
int cd_cmd(char **args, char *initial_directory);
int pwd_cmd(void);
int echo_cmd(char **args, char **env);
int env_cmd(char **env);
int which_cmd(char **args, char **env);

#endif /* SHELL_H */
