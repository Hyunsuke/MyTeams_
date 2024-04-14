/*
** EPITECH PROJECT, 2024
** modif_login.c
** File description:
** modif client when log in
*/

#include "server.h"

int loop_to_update(client_t *current, char *name, int fd)
{
    if (current->next->fd == fd) {
        if (current->next->log == false) {
            free(current->next->name);
            current->next->name = strdup(name);
            current->next->log = true;
            return 0;
        } else {
            write(current->next->fd, "Client already log\n",
                strlen("Client already log\n"));
            return 84;
        }
    }
    return 0;
}

int update_with_one_client(client_t *current, int fd, char *name)
{
    if (current->fd == fd) {
        if (current->log == false) {
            free(current->name);
            current->name = strdup(name);
            current->log = true;
            return 0;
        } else {
            write(current->fd, "Client already log\n",
                strlen("Client already log\n"));
            return 84;
        }
    }
    return 0;
}

int update_client_name(client_t **head, int fd, char *name)
{
    client_t *current = *head;

    if (current == NULL) {
        printf("La liste est vide.\n");
        return 0;
    }
    if (update_with_one_client(current, fd, name) == 84)
        return 84;
    while (current->next != NULL) {
        if (loop_to_update(current, name, fd) == 84)
            return 84;
        current = current->next;
    }
    return 0;
}
