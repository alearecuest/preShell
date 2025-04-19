/**
 * execute_command - Ejecuta un comando
 * @command: El comando a ejecutar
 * @prog_name: El nombre del programa (para mensajes de error)
 * Return: Estado de salida del comando
 */
int execute_command(char *command, char *prog_name)
{
	pid_t child_pid;
	int status = 0;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	if (child_pid == -1)
	{
		perror("Error en fork");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, command);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (status);
}
