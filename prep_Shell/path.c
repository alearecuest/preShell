/**
 * find_in_path - Busca un comando en el PATH
 * @command: El comando a buscar
 * Return: La ruta completa del comando o NULL si no se encuentra
 */
char *find_in_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	int cmd_len, dir_len;
	struct stat st;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return strdup(command);
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	cmd_len = strlen(command);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		dir_len = strlen(dir);

		full_path = malloc(dir_len + cmd_len + 2);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Ejecuta un comando buscándolo en el PATH
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
