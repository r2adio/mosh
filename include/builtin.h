#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUILTIN_COUNT (sizeof(builtins) / sizeof(builtins[0]))

int builtin(char **args, char **env, char *init_dir);

int cd_cmd(char **args, char **env, char *init_dir);
int pwd_cmd(char **args, char **env, char *init_dir);
int echo_cmd(char **args, char **env, char *init_dir);
int env_cmd(char **args, char **env, char *init_dir);
int which_cmd(char **args, char **env, char *init_dir);
int exit_cmd(char **args, char **env, char *init_dir);
