#include "shell.h"

#define TOKEN_DELIM " \n\t\r"

/**
 * tokenize - divides a string into tokens
 * @str: string to tokenize
 *
 * Return: array of tokens
 */
char **tokenize(char *str)
{
	char **arguments = NULL;
	char *token;
	int i = 0;

	arguments = malloc(sizeof(char *) * 1024);
	if (!arguments)
		return (NULL);
	token = strtok(str, TOKEN_DELIM);
	while (token)
	{
		arguments[i] = strdup(token);
		if (!arguments[i])
		{
			free_tokens(arguments);
			return (NULL);
		}
		token = strtok(NULL, TOKEN_DELIM);
		i++;
	}
	arguments[i] = NULL;
	return (arguments);
}

/**
 * free_tokens - frees the array of tokens
 * @arguments: array to be freed
 *
 * Return: void
 */
void free_tokens(char **arguments)
{
	if (arguments)
	{
		int i = 0;

		while (arguments[i] != NULL)
		{
			free(arguments[i]);
			i++;
		}
		free(arguments);
	}
}
