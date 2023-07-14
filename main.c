#include "shell.h"

/**
 * prompt - prints the prompt
 *
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		char promptStr[] = "$ ";

		write(STDOUT_FILENO, promptStr, sizeof(promptStr) - 1);
	}
}

/**
 * main - main function
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t length = 0;
	ssize_t status;
	char **argument;

	(void)argc;
	while (1)
	{
		prompt();
		status = getline(&buffer, &length, stdin);
		if (status == -1)
		{
			free(buffer);
			exit(0);
		}
		argument = tokenize(buffer);
		if (argument == NULL)
			continue;

		execute(argv[0], argument);

		free_tokens(argument);
		free(buffer);
		buffer = NULL;
		length = 0;
	}
	return (0);
}
