#include "shell.h"

/**
 * shell_setenv - Set a new environment variable or modify an existing one.
 * @args: Arguments array for setenv command.
 *
 * Return: 0 on success, -1 on failure.
 */
int shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * shell_unsetenv - Remove an environment variable.
 * @args: Arguments array for unsetenv command.
 *
 * Return: 0 on success, -1 on failure.
 */
int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
