#include "shell.h"

/**
 * main - Punto de entrada del shell
 * @ac: Número de argumentos
 * @av: Array de argumentos
 * Return: 0 en caso de éxito
 */
int main(int ac, char **av)
{
	char *command = NULL;
	int status = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		command = read_command();

		if (command == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (command[0] != '\0')
			status = execute_command(command, av[0]);

		free(command);
	}

	return (status);
}

/**
 * read_command - Lee un comando de la entrada estándar
 * Return: El comando leído o NULL en caso de EOF o error
 */
char *read_command(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &bufsize, stdin);

	if (chars_read == -1)
	{
		free(line);
		return NULL;
	}

	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}
