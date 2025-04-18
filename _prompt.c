#include <stdio.h>
#include <stdlib.h>
/**
 * main - Entry Point
 * Return: 0 if success
 */

int main (void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &n, stdin);

		if (read == -1)
		{
			free(line);
			break;
		}
		printf("%s", line);
	}
	return (0);
}
