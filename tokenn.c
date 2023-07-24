#include "shell.h"

#define TOKEN_DELIM " \n\t\r"
#define MAX_TOKENS 1024
/**
 * tokenize - divides a string into tokens
 * @str: string to tokenize
 *
 * Return: array of tokens
 */
char **tokenize(char *str)
{
	char **arguments = NULL;
	char *expanded_token;
	char *token;
	int i = 0;

	arguments = malloc(sizeof(char *) * MAX_TOKENS);
	if (!arguments)
		return (NULL);
	token = strtok(str, TOKEN_DELIM);
	while (token)
	{
		if (token[0] == '$')
		{
			expanded_token = expand_variables(token);
			if (!expanded_token)
			{
				fprintf(stderr, "Error: Variable expansion failed\n");
				free_tokens(arguments);
				return (NULL);
			}
			arguments[i] = expanded_token;
		}
		else if (token[0] != '#')
		{
			arguments[i] = strdup(token);
			if (!arguments[i])
			{
				fprintf(stderr, "Error: Memory allocation failed\n");
				free_tokens(arguments);
				return (NULL);
			}
		}
		i++;
		token = strtok(NULL, TOKEN_DELIM);
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
/**
 * expand_variables - Expands variables in a given token.
 * @token: Token to expand.
 *
 * Return: The expanded token or NULL on failure.
 */
char *expand_variables(char *token)
{
	if (strcmp(token, "$?") == 0)
	{
		char status_str[10];

		snprintf(status_str, sizeof(status_str), "%d", last_status);
		return (strdup(status_str));
	}
	else if (strcmp(token, "$$") == 0)
	{
		char pid_str[10];

		snprintf(pid_str, sizeof(pid_str), "%d", getpid());
		return (strdup(pid_str));
	}
	else if (token[0] == '$')
	{
		char *var_name;
		char *env_value;

		var_name = token + 1;
		env_value = getenv(var_name);
		if (env_value)
			return (strdup(env_value));
		else
			return (strdup(""));
	}
	return (strdup(token));
}
