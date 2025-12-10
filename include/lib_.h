#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// compares 2 strings(s1, s2) upto n characters
int strcmp_(const char *s1, const char *s2, size_t n);

// counts the number of characters in a given string
size_t strlen_(const char *s);

char *getenv_(const char *name, char **env);
