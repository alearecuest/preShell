#include "shell.h"

/**
 * tokenize - Divide un comando en tokens (palabras)
 * @command: El comando a dividir
 * Return: Un array de strings con los tokens
 */
char **tokenize(char *command)
{
	char **tokens = NULL;
	char *token;
	int i = 0;
	char *delim = " \t\r\n\a";
	char *command_copy;

	command_copy = strdup(command);
	if (!command_copy)
	{
		perror("Error de memoria");
		exit(1);
	}

	tokens = malloc(sizeof(char *) * 64);
	if (!tokens)
	{
		perror("Error de memoria");
		free(command_copy);
		exit(1);
	}

	token = strtok(command_copy, delim);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("Error de memoria");
			while (--i >= 0)
				free(tokens[i]);
			free(tokens);
			free(command_copy);
			exit(1);
		}
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;

	free(command_copy);
	return (tokens);
}

/**
 * free_tokens - Libera la memoria asignada para los tokens
 * @tokens: Array de tokens a liberar
 */
void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]);

	free(tokens);
}
