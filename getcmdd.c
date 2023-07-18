#include "shell.h"

/**
 * get_command_location - returns the full path of a command
 * @command: the command
 *
 * Return: pointer to the full path
 */
char *get_command_location(const char *command)
{
	char *path_env, *path, *full_path;

	path_env = getenv("PATH");

	if (!path_env)
		return (NULL);

	path = strdup(path_env);

	if (!path)
		return (NULL);

	full_path = find_command_in_path(command, path);
	free(path);

	if (!full_path)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
	}
	return (full_path);
}

/**
 * find_command_in_path - finds the command in the given path
 * @command: the command
 * @path: the PATH environment variable
 *
 * Return: pointer to the full path or NULL if not found
 */
char *find_command_in_path(const char *command, const char *path)
{
	char *token, *copy_path, *full_path;
	int length;

	copy_path = strdup(path);

	if (!copy_path)
		return (NULL);

	token = strtok(copy_path, ":");
	while (token)
	{
		length = strlen(token) + strlen(command) + 2;
		full_path = build_full_path(token, command, length);

		if (!full_path)
		{
			free(copy_path);
			return (NULL);
		}
		if (access(full_path, F_OK) == 0)
		{
			free(copy_path);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (NULL);
}

/**
 * build_full_path - builds the full path by concatenating directory and
 * command
 * @directory: the directory path
 * @command: the command
 * @length: the total length of the full path
 *
 * Return: pointer to the full path or NULL if not enough memory
 */
char *build_full_path(const char *directory, const char *command, int length)
{
	char *full_path;

	full_path = malloc(sizeof(char) * length);

	if (!full_path)
		return (NULL);

	snprintf(full_path, length, "%s/%s", directory, command);
	return (full_path);
}
