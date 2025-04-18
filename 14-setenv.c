#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - cambia o añade una variable de entorno
 * @name: nombre de la variable
 * @value: valor de la variable
 * @overwrite: sobrescribir si ya existe
 *
 * Return: 0 en caso de éxito, -1 en caso de error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    int i = 0;
    char *env_var, *new_var;
    size_t name_len;
    
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL || value == NULL)
    {
        return (-1);  /* Parámetros inválidos */
    }
    
    name_len = strlen(name);
    
    while (environ[i] != NULL)
    {
        env_var = environ[i];
        
        if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
        {
            if (!overwrite)
                return (0);  /* No sobrescribir */
            
            new_var = malloc(name_len + strlen(value) + 2);  /* +2 por '=' y '\0' */
            if (new_var == NULL)
                return (-1);
            
            sprintf(new_var, "%s=%s", name, value);
            
            free(environ[i]);  /* Cuidado: esto asume que environ es modificable */
            environ[i] = new_var;
            
            return (0);
        }
        
        i++;
    }
    
    new_var = malloc(name_len + strlen(value) + 2);
    if (new_var == NULL)
        return (-1);
    
    sprintf(new_var, "%s=%s", name, value);
    
    printf("Nota: esta implementación simplificada no puede añadir nuevas variables\n");
    printf("Variable a añadir: %s\n", new_var);
    
    free(new_var);
    return (-1);
}

/**
 * main - prueba la función _setenv
 *
 * Return: Always 0.
 */
int main(void)
{
    char *value;
    
    value = getenv("TESTVAR");
    if (value != NULL)
        printf("TESTVAR actual: %s\n", value);
    else
        printf("TESTVAR no existe actualmente\n");
    
    if (_setenv("TESTVAR", "nuevo_valor", 1) == 0)
        printf("Variable cambiada con éxito\n");
    else
        printf("Error al cambiar la variable\n");
    
    value = getenv("TESTVAR");
    if (value != NULL)
        printf("TESTVAR después del cambio: %s\n", value);
    else
        printf("TESTVAR no existe después del cambio\n");
    
    return (0);
}
