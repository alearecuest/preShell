#include <stdio.h>
#include <stdlib.h>

/**
 * main - imprime un prompt, lee una línea y la imprime
 *
 * Return: Always 0.
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1)
    {
        printf("$ ");
        characters = getline(&buffer, &bufsize, stdin);
        
        if (characters == -1)
	{
            printf("\n");
            break;
        }

        printf("%s", buffer);
    }
    free(buffer);
    return (0);
}
