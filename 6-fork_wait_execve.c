#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - crea 5 procesos hijos que ejecutan ls -l /tmp
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t child_pid;
    int status;
    int i;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
    
    for (i = 0; i < 5; i++)
    {
        child_pid = fork();
        
        if (child_pid == -1)
        {
            perror("Error:");
            return (1);
        }
        
        if (child_pid == 0)
        {
            printf("Hijo %d ejecutando ls -l /tmp:\n", i + 1);
            
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("Error:");
                return (1);
            }
        
            return (0);
        }
        else
        {
            wait(&status);
            printf("Hijo %d ha terminado\n", i + 1);
        }
    }
    
    return (0);
}
