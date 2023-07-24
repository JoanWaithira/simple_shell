#include "shell.h"

/**
 * cd - Change the current directory of the process.
 * @args: Arguments array for cd command.
 * @current_dir: Buffer to store the current directory path.
 * @current_dir_size: Size of the current directory buffer.
 *
 * Return: 0 on success, -1 on error.
 */
int cd(char **args, char *current_dir, int current_dir_size)
{
	char *new_dir;

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		new_dir = getenv("HOME");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: No home directory found.\n");
			return (-1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: No previous directory found.\n");
			return (-1);
		}
		printf("%s\n", new_dir);
	}
	else
	{
		new_dir = args[1];
	}
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (getcwd(current_dir, current_dir_size) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	setenv("PWD", current_dir, 1);
	return (0);
}
