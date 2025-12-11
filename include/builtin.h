#pragma once

#define _GNU_SOURCE

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int builtin(char **args, char **env, char *init_dir);

int cd_cmd(char **args, char *initial_directory);
int pwd_cmd(void);
int echo_cmd(char **args, char **env);
int env_cmd(char **env);
int which_cmd(char **args, char **env);
