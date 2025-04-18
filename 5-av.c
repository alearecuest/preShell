#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - divide una cadena en palabras
 * @str: cadena a dividir
 *
 * Return: array de strings
 */
char **split_string(char *str)
{
    char **words = NULL;
    char *token;
    int i = 0;
    int size = 10;
    
    words = malloc(sizeof(char *) * size);
    if (words == NULL)
        return (NULL);
    
    token = strtok(str, " \t\n");
    
    while (token != NULL)
    {
        words[i] = token;
        i++;
        
        if (i >= size - 1)
        {
            size *= 2;
            words = realloc(words, sizeof(char *) * size);
            if (words == NULL)
                return (NULL);
        }
        
        token = strtok(NULL, " \t\n");
    }
    
    words[i] = NULL;
    return (words);
}

/**
 * main - prueba la función split_string
 *
 * Return: Always 0.
 */
int main(void)
{
    char str[] = "Hola mundo esto es una prueba";
    char **words;
    int i;
    
    words = split_string(str);
    
    for (i = 0; words[i] != NULL; i++)
    {
        printf("Palabra %d: %s\n", i, words[i]);
    }
    
    free(words);
    return (0);
}
