#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * main - busca archivos en el PATH
 * @ac: número de argumentos
 * @av: array de argumentos
 *
 * Return: 0 en caso de éxito, 1 en caso de error
 */
int main(int ac, char **av)
{
    char *path, *path_copy, *token, *file_path;
    int i, found;
    struct stat st;
    
    if (ac < 2)
    {
        printf("Usage: %s filename ...\n", av[0]);
        return (1);
    }
    
    path = getenv("PATH");
    if (path == NULL)
    {
        printf("PATH no encontrado\n");
        return (1);
    }
    
    for (i = 1; i < ac; i++)
    {
        found = 0;
        path_copy = strdup(path);
        
        token = strtok(path_copy, ":");
        while (token != NULL)
        {
            file_path = malloc(strlen(token) + strlen(av[i]) + 2); /* +2 por '/' y '\0' */
            sprintf(file_path, "%s/%s", token, av[i]);
            
            if (stat(file_path, &st) == 0 && access(file_path, X_OK) == 0)
            {
                printf("%s: %s\n", av[i], file_path);
                found = 1;
                free(file_path);
                break;
            }
            
            free(file_path);
            token = strtok(NULL, ":");
        }
        
        if (!found)
            printf("%s: not found\n", av[i]);
        
        free(path_copy);
    }
    
    return (0);
}
