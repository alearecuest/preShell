#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern char **environ;  /* Declaración de la variable global environ */

/**
 * _getenv - obtiene el valor de una variable de entorno
 * @name: nombre de la variable
 *
 * Return: puntero al valor de la variable, o NULL si no existe
 */
char *_getenv(const char *name)
{
    int i = 0;
    char *env_var;
    size_t name_len = strlen(name);
    
    while (environ[i] != NULL)
    {
        env_var = environ[i];
        
        if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
        {
            return (env_var + name_len + 1);
        }
        
        i++;
    }
    
    return (NULL);  /* Variable no encontrada */
}

/**
 * main - prueba la función _getenv
 *
 * Return: Always 0.
 */
int main(void)
{
    char *value;
    
    value = _getenv("PATH");
    printf("PATH: %s\n", value);
    
    value = _getenv("HOME");
    printf("HOME: %s\n", value);
    
    value = _getenv("VARIABLE_QUE_NO_EXISTE");
    if (value == NULL)
        printf("VARIABLE_QUE_NO_EXISTE no está definida\n");
    else
        printf("VARIABLE_QUE_NO_EXISTE: %s\n", value);
    
    return (0);
}
