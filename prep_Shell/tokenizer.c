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

	tokens = malloc(sizeof(char *) * 64);
	if (!tokens)
	{
		perror("Error de memoria");
		exit(1);
	}

	token = strtok(command, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * execute_command - Ejecuta un comando con argumentos
 * @command: El comando a ejecutar
 * @prog_name: El nombre del programa (para mensajes de error)
 * Return: Estado de salida del comando
 */
int execute_command(char *command, char *prog_name)
{
	pid_t child_pid;
	int status = 0;
	char **args;

	args = tokenize(command);

	if (!args[0])
	{
		free(args);
		return (0);
	}

	child_pid = fork();
    
    if (child_pid == -1) /* Error al crear el proceso */
    {
        perror("Error en fork");
        free(args);
        return (1);
    }

    if (child_pid == 0)
    {
	    if (execve(args[0], args, environ) == -1)
	    {
		    fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		    free(args);
		    exit(127);
	    }
    }
    else
    {
	    waitpid(child_pid, &status, 0);
	    free(args);

	    if (WIFEXITED(status))
		    return (WEXITSTATUS(status));
    }
    return (status);
}
