#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char **parser(char *input);
void free_tokens(char **tokens);
