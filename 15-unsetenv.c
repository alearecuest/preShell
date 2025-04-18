#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _unsetenv - elimina una variable del entorno
 * @name: nombre de la variable
 *
 * Return: 0 en caso de éxito, -1 en caso de error
 */
int _unsetenv(const char *name)
{
    int i = 0, j;
    size_t name_len;
    
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
    {
        return (-1);
    }
    
    name_len = strlen(name);
    
    while (environ[i] != NULL)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            free(environ[i]);
            
            for (j = i; environ[j] != NULL; j++)
            {
                environ[j] = environ[j + 1];
            }
            
            return (0);
        }
        
        i++;
    }
    return (0);
}

/**
 * main - prueba de la función _unsetenv
 *
 * Return: Always 0.
 */
int main(void)
{
    char *value;
    
    setenv("TESTVAR", "valor_prueba", 1);
    
    value = getenv("TESTVAR");
    if (value != NULL)
        printf("TESTVAR antes de unsetenv: %s\n", value);
    else
        printf("TESTVAR no existe antes de unsetenv\n");
    
    if (_unsetenv("TESTVAR") == 0)
        printf("Variable eliminada con éxito\n");
    else
        printf("Error al eliminar la variable\n");
    
    value = getenv("TESTVAR");
    if (value != NULL)
        printf("TESTVAR después de unsetenv: %s\n", value);
    else
        printf("TESTVAR ya no existe después de unsetenv\n");
    
    return (0);
}
