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
int execute(char *program_name, char **args);
char *get_command_location(const char *command);
char *find_command_in_path(const char *command, const char *path);
char *build_full_path(const char *directory, const char *command, int length);
void execute_custom_command(char *program_name, char **args);
void execute_env(void);
void execute_exit(char **args);
void prompt(void);
int main(int argc, char **argv);
char **tokenize(char *str);
void free_tokens(char **arguments);
ssize_t _getline(char **line);
ssize_t refill_buffer(char *buffer, ssize_t *pos, ssize_t *bytes_read);
int read_char(char *buffer, ssize_t *pos, ssize_t bytes_read);

extern char **environ;
#endif
