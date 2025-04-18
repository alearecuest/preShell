#include <stdio.h>
#include <unistd.h>

extern char **environ;

/**
 * main - imprime el entorno usando environ
 *
 * Return: Always 0.
 */
int main(void)
{
    int i = 0;
    
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    
    return (0);
}
