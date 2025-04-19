#include "shell.h"

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
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
