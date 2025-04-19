#include "shell.h"

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
