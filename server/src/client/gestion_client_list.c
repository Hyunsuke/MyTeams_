/*
** EPITECH PROJECT, 2024
** gestion_list.c
** File description:
** basic functions for list usage
*/

#include "server.h"

void display_clients(server_t *s)
{
    client_t *current_client = s->clients;
    int client_num = 1;

    printf("Liste clients:\n");
    if (current_client == NULL)
        printf("Liste client vide\n");
    while (current_client != NULL) {
        if (current_client->name != NULL)
            printf("Client %d: [%s] et [%d]\n", client_num,
                current_client->name, current_client->fd);
        else
            printf("Client %d: [%s] et [%d]\n", client_num, "No Name",
                current_client->fd);
        current_client = current_client->next;
        client_num++;
    }
}

client_t *create_client(int fd)
{
    client_t *new_client = my_malloc(sizeof(client_t));

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
    if (s->save_struct->is_saving)
        FD_CLR(current->fd, &s->client_fds);
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

client_t *find_client_by_name(client_t *head, const char *name)
{
    client_t *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
