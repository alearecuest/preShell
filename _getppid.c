#include <stdio.h>
#include <unistd.h>

/**
 * main - imprime el PID del proceso padre
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t parent_pid;

    parent_pid = getppid();
    printf("PID del proceso padre: %u\n", parent_pid);
    return (0);
}
