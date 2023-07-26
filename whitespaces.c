#include "shell.h"

/**
 * trim_whitespaces- A function to remove bpoth leading and trailing
 * white spaces
 * @str: The command inputted
 */

void trim_whitespaces(char *str)
{
	size_t len = strlen(str);
	size_t start = 0;
	size_t  end = len - 1;
	size_t i;
	size_t j;

	while (isspace((unsigned char)str[start]))
	{
		start++;
	}
	if (start == len)
	{
		str[0] = '\0';
		return;
	}
	while (isspace((unsigned char)str[end]) && end > start)
	{
		end--;
	}
	for (i = start, j = 0; i <= end; i++, j++)
	{
		str[j] = str[i];
	}
	str[j] = '\0';
}
