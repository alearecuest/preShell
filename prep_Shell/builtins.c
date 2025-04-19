/**
 * builtin_exit - Implementación del comando exit
 * Return: No retorna, termina el programa
 */
int builtin_exit(void)
{
	exit(0);
}

/**
 * builtin_env - Implementación del comando env
 * Return: Siempre retorna 0
 */
int builtin_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}

/**
 * execute_command - Ejecuta un comando o comando integrado
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
		free(args);
		return (0);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (builtin_exit());
	}
	else if (strcmp(args[0], "env") == 0)
	{
		free(args);
		return (builtin_env());
	}

	full_path = find_in_path(args[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free(args);
		return (127);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error en fork");
		free(args);
		free(full_path);
		return (1);
	}

	if (child_pid == 0)
	{
		args[0] = full_path;

		if (execve(full_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
			free(args);
			free(full_path);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		free(args);
		free(full_path);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (status);
}
