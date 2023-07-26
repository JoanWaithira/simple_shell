#include "shell.h"

/**
 * read_char - Read a single character from the buffer
 * @buffer: Pointer to the buffer to read data from
 * @pos: Pointer to the current position in the buffer
 * @bytes_read: Number of bytes read in the buffer
 * Return: The character read, or -1 on failure or end of input
 */
int read_char(char *buffer, ssize_t *pos, ssize_t bytes_read)
{
	if (*pos >= bytes_read)
	{
		return (refill_buffer(buffer, pos, &bytes_read)
				== 0 ? -1 : buffer[(*pos)++]);
	}
	return (buffer[(*pos)++]);
}
/**
 * _getline - function to read input from the user
 * @line: Pointer to a buffer to store the input line
 * Return: Number of characters read (including '\n'), or -1 on failure
 */
ssize_t _getline(char **line)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t pos, bytes_read;
	ssize_t i, n = 0;
	char *line = NULL;

	while (1)
	{
		if ((read_char(buffer, &pos, bytes_read)) == -1)
		{
			if (n > 0)
			{
				*line = malloc(n + 1);
				if (!*line)
				{
					perror("Memory allocation error");
					return (-1);
				} for (i = 0; i < n; i++)
					(*line)[i] = buffer[i];
				(*line)[n] = '\0';
				pos++;
				return (n + 1);
			} else
				return (-1);
		}
		if ((read_char(buffer, &pos, bytes_read)) == '\n')
		{
			*line = malloc(n + 1);
			if (!*line)
			{
				perror("Memory allocation error");
				return (-1);
			} for (i = 0; i < n; i++)
				(*line)[i] = buffer[i];
			(*line)[n] = '\0';
			pos++;
			return (n + 1);
		}
		n++;
	}
}
