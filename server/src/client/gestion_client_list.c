/*
** EPITECH PROJECT, 2024
** gestion_list.c
** File description:
** basic functions for list usage
*/

#include "server.h"

client_t *create_client(int fd)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (new_client != NULL) {
        new_client->fd = fd;
        new_client->log = false;
        new_client->name = NULL;
        new_client->next = NULL;
    }
    return new_client;
}

void remove_client(client_t **head, int fd, server_t *s)
{
    client_t *current = *head;
    client_t *prev = NULL;

    while (current != NULL && current->fd != fd) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Client non trouvé.\n");
        return;
    }
    if (prev == NULL)
        *head = current->next;
    else
        prev->next = current->next;
    close(current->fd);
    FD_CLR(current->fd, &s->client_fds);
    free(current);
}

void add_client(client_t **head, int fd)
{
    client_t *new_client = create_client(fd);
    client_t *current = *head;

    if (new_client == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_client;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_client;
    }
}
