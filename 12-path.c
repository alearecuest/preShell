#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path_directories - imprime cada directorio en PATH
 *
 * Return: number of directories printed
 */
int print_path_directories(void)
{
    char *path, *path_copy, *token;
    int count = 0;
    
    path = getenv("PATH");
    if (path == NULL)
    {
        printf("PATH no encontrado\n");
        return (0);
    }
    
    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        printf("Error al asignar memoria\n");
        return (0);
    }
    
    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        printf("%s\n", token);
        count++;
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return (count);
}

/**
 * main - prueba la función print_path_directories
 *
 * Return: Always 0.
 */
int main(void)
{
    int dirs;
    
    dirs = print_path_directories();
    printf("\nTotal de directorios en PATH: %d\n", dirs);
    
    return (0);
}
