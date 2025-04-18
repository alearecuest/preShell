#include <stdio.h>

/**
 * main - imprime todos los argumentos sin usar ac
 *
 * @ac: count of arguments (not used)
 * @av: array of arguments
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    int i = 0;

    while (av[i] != NULL)
    {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}
