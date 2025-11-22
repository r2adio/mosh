#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// compares 2 strings(s1, s2) upto n characters
int strcmp_(char *s1, char *s2, size_t n);

// counts the number of characters in a given string
size_t strlen_(char *s);

// duplicate the char to a string and returns its pointer
char *chardup_(char c);
size_t puts_(char *s);
#define putchar_(c) write(1, chardup_(c), 1)
int printf_();
