#include "shell.h"

/**
 * execute - executes a command
 * @program_name: name of the program
 * @args: the commands
 *
 * Return: 0 on success
 */
int execute(char *program_name, char **args)
{
	char *command = args[0];

	if (command == NULL)
		return (0);

	if (strcmp(command, "exit") == 0)
	{
		execute_exit(args);
	}
	else if (strcmp(command, "env") == 0)
	{
		execute_env();
	}
	else
	{
		execute_custom_command(program_name, args);
	}
	return (0);
}

/**
 * execute_exit - handles the "exit" command
 * @args: the commands
 */
void execute_exit(char **args)
{
	free_tokens(args);
	printf("You are exiting the shell. So sad to see you go :(\n");
	exit(0);
}

/**
 * execute_env - handles the "env" command
 */
void execute_env(void)
{
	print_environment();
}

/**
 * execute_custom_command - executes a custom command
 * @program_name: name of the program
 * @args: the commands
 */
void execute_custom_command(char *program_name, char **args)
{
	char *command = args[0];
	pid_t pid;
	char *command_path;
	int status;

	command_path = get_command_location(command);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %s: command not found\n", program_name, command);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error creating child process");
	}
	else if (pid == 0)
	{
		if (execve(command_path, args, NULL) == -1)
		{
			perror("Execution error");
			exit(0);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("Error waiting for child process");
	}
	free(command_path);
}
