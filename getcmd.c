#include "shell.h"
/**
 * get_command_location - returns the full path of a command
 * @command: the command
 *
 * Return: pointer to the full path
 */
char *get_command_location(const char *command)
{
	char *path_env, *token, *full_path, *path;
	int length;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path = strdup(path_env);
	if (!path)
		return (NULL);

	token = strtok(path, ":");
	while (token)
	{
		length = strlen(token) + strlen(command) + 2;
		full_path = malloc(sizeof(char) * length);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}
		snprintf(full_path, length, "%s/%s", token, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path);
	if (access(command, X_OK) == 0)
		return (strdup(command));

	return (NULL);
}
