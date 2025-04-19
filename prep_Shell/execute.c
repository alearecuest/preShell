#include "shell.h"

/**
 * execute_command - Ejecuta un comando con argumentos y búsqueda en PATH
 * @command: El comando a ejecutar
 * @prog_name: El nombre del programa (para mensajes de error)
 * Return: Estado de salida del comando
 */
int execute_command(char *command, char *prog_name)
{
	pid_t child_pid;
	int status = 0;
	char **args;
	char *full_path;

	args = tokenize(command);

	if (!args[0])
	{
		free_tokens(args);
		return (0);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		return (builtin_exit());
	}
	else if (strcmp(args[0], "env") == 0)
	{
		free_tokens(args);
		return (builtin_env());
	}

	full_path = find_in_path(args[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		return (127);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error en fork");
		free(full_path);
		free_tokens(args);
		return (1);
	}

	if (child_pid == 0)
	{
		free(args[0]);
		args[0] = full_path;

		if (execve(full_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
			free_tokens(args);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		free(full_path);
		free_tokens(args);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (status);
}
