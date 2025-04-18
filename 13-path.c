#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct path_dir - nodo para la lista enlazada de directorios
 * @dir: string del directorio
 * @next: puntero al siguiente nodo
 */
typedef struct path_dir
{
    char *dir;
    struct path_dir *next;
} path_dir_t;

/**
 * build_path_list - construye una lista enlazada de directorios de PATH
 *
 * Return: puntero a la cabeza de la lista, o NULL en caso de error
 */
path_dir_t *build_path_list(void)
{
    char *path, *path_copy, *token;
    path_dir_t *head = NULL, *new_node, *current;
    
    /* Obtener el PATH del entorno */
    path = getenv("PATH");
    if (path == NULL)
    {
        printf("PATH no encontrado\n");
        return (NULL);
    }
    
    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        printf("Error al asignar memoria\n");
        return (NULL);
    }
    
    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        new_node = malloc(sizeof(path_dir_t));
        if (new_node == NULL)
        {
            printf("Error al asignar memoria\n");
            free(path_copy);
            return (NULL);
        }
        
        new_node->dir = strdup(token);
        if (new_node->dir == NULL)
        {
            printf("Error al asignar memoria\n");
            free(new_node);
            free(path_copy);
            return (NULL);
        }
        
        new_node->next = NULL;
        
        if (head == NULL)
        {
            head = new_node;
            current = head;
        }
        else
        {
            current->next = new_node;
            current = new_node;
        }
        
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return (head);
}

/**
 * free_path_list - libera la memoria de la lista enlazada
 * @head: puntero a la cabeza de la lista
 */
void free_path_list(path_dir_t *head)
{
    path_dir_t *current, *next;
    
    current = head;
    while (current != NULL)
    {
        next = current->next;
        free(current->dir);
        free(current);
        current = next;
    }
}

/**
 * print_path_list - imprime la lista enlazada
 * @head: puntero a la cabeza de la lista
 */
void print_path_list(path_dir_t *head)
{
    path_dir_t *current = head;
    int i = 0;
    
    while (current != NULL)
    {
        printf("[%d] %s\n", i, current->dir);
        current = current->next;
        i++;
    }
}

/**
 * main - prueba las funciones de lista enlazada
 *
 * Return: Always 0.
 */
int main(void)
{
    path_dir_t *path_list;
    
    path_list = build_path_list();
    if (path_list == NULL)
    {
        printf("Error al construir la lista\n");
        return (1);
    }
    
    printf("Lista de directorios en PATH:\n");
    print_path_list(path_list);
    
    free_path_list(path_list);
    return (0);
}
