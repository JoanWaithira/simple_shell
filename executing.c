#include "shell.h"

/**
 * execute_exit - A function to execute the exit command
 * @av: Argument
 */
void execute_exit(char **av)
{
	free_tokens(av);
	printf("You are exiting the shell .. So sad to see you go:(\n");
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
 * execute_command - A function to execute othet commands
 * @argv - Argument vector
 * @av - Argument
 */

void execute_command(char *argv, char **av)
{
	char *command = av[0];
	char *command_path;
	pid_t pid;
	int status;

	command_path = get_command_location(command);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %s: command not found \n", argv, command);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error creating child process");
	}
	else if (pid == 0)
	{
		if (execve(command_path, av, NULL) == -1)
		{
			perror("Execution error");
			exit(0);
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("Error waiting for child process");
				exit(0);
			}
		}
	}
	free (command_path);
}
/**
 * execute - A function that executes commands
 * @argv: argument vector
 * @av: arguments
 */

int execute(char *argv, char **av)
{
	char *command = av[0];

	if (command == NULL)
	{
		return (0);
	}
	if (strcmp(command, "exit") == 0)
	{
	execute_exit(av);
	}	
	else if (strcmp(command, "env") == 0)
	{
		print_environment();
	}
	else
	{
		execute_command(argv, av);
	}	
	return (0);
}
