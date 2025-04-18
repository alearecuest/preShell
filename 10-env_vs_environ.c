#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern char **environ;  /* Declaración de la variable global environ */

/**
 * main - compara env y environ
 * @ac: argumentos count
 * @av: argumentos vector
 * @env: entorno
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    printf("Dirección de env (3er parámetro de main): %p\n", (void *)env);
    printf("Dirección de environ (variable global): %p\n", (void *)environ);
    
    if (env == environ)
        printf("env y environ son iguales\n");
    else
        printf("env y environ son diferentes\n");
    
    int i = 0;
    
    printf("\nComparando contenidos:\n");
    while (env[i] != NULL && environ[i] != NULL)
    {
        if (strcmp(env[i], environ[i]) != 0)
        {
            printf("Diferencia encontrada en la posición %d\n", i);
            printf("env[%d]: %s\n", i, env[i]);
            printf("environ[%d]: %s\n", i, environ[i]);
            break;
        }
        i++;
    }
    
    if (env[i] == NULL && environ[i] == NULL)
        printf("Todos los contenidos son idénticos\n");
    
    return (0);
}
