#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// compares 2 strings(s1, s2) upto n characters
int strcmp_(char *s1, char *s2, size_t n);

// counts the number of characters in a given string
size_t strlen_(char *s);

int printf_();
