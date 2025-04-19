#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void display_prompt(void);
char *read_comand(void);
int execute_command(char *command, char *prog_name);

extern char **environ;

#endif /* SHELL_H */
