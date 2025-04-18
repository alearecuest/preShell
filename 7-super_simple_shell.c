#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    pid_t child_pid;
    int status;
    char *argv[2];

    while (1)
    {
        printf("#cisfun$ ");
        characters = getline(&buffer, &bufsize, stdin);
        
        if (characters == -1)
        {
            printf("\n");
            break;
        }
        
        if (buffer[characters - 1] == '\n')
            buffer[characters - 1] = '\0';
        
        argv[0] = buffer;
        argv[1] = NULL;
        
        child_pid = fork();
        
        if (child_pid == -1)
        {
            perror("Error:");
            continue;
        }
        
        if (child_pid == 0)
        {
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("Error:");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }
    
    free(buffer);
    return (0);
}
