#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFF_SIZE 1024

void print_environment(void);
int execute(char *argv, char **av);
int _putchar(char c);
char *get_command_location(const char *command);
void prompt(void);
int main(int argc, char **argv);
char **tokenize(char *str);
void free_tokens(char **arguments);
void prompt(void);

extern char **environ;
#endif
