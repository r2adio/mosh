#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **parser(char *input);
void free_tokens(char **tokens);
int builtin(char **args, char **env, char *init_dir);
