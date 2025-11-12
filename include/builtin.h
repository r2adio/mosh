#ifndef BUILTIN_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int builtin(char **args, char **env, char *init_dir);

int cd_cmd(char **args, char *initial_directory);
int pwd_cmd(void);
int echo_cmd(char **args, char **env);
int env_cmd(char **env);
int which_cmd(char **args, char **env);

#endif // !BUILTIN_H
