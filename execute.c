#include "shell.h"
/**
 * execute - executes a command
 * @argv: name of the program
 * @av: the commands
 *
 * Return: 0 on success
 */
int execute(char *argv, char **av)
{
	char *command = av[0], *command_path;
	pid_t pid;
	int status = 0;

	if (command == NULL)
		return (status);
	if (strcmp(command, "exit") == 0)
	{
		free_tokens(av);
		printf("You are exiting the shell.. So sad to see you go:(\n");
		exit(0);
	}
	if (strcmp(command, "env") == 0)
	{
		print_environment();
	}
	else
	{
		command_path = get_command_location(command);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: %s: command not found\n", argv, command);
			return (0);
		}
		pid = fork();
		if (pid == -1)
			perror("Error");
		else if (pid == 0)
		{
			if (execve(command_path, av, NULL) == -1)
			{
				perror("Error: ");
				exit(0);
			}
		}
		else if (waitpid(pid, &status, 0) == -1)
			perror("Error: ");
		free(command_path);
	}
	return (status);
}
