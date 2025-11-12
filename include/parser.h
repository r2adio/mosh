#ifndef PARSER_H
#define PARSER_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **parser(char *input);
void free_tokens(char **tokens);
int builtin(char **args, char **env, char *init_dir);

#endif // PARSER_H
