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
            printf("Client %d: [%s] et [%d]\n", client_num, current_client->name, current_client->fd);
        else
            printf("Client %d: [%s] et [%d]\n", client_num, "No Name", current_client->fd);
        current_client = current_client->next;
        client_num++;
    }
}

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

void add_client(client_t **head, int fd)
{
    client_t *new_client = create_client(fd);
    client_t *current = *head;

    if (new_client == NULL) {
        printf("Error in client creation\n");
        return;
    }

    if (current == NULL) {
        *head = new_client; // Met à jour le pointeur de tête
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_client;
    }
}

void remove_client(client_t **head, int fd, server_t *s)
{
    client_t *current = *head;

    if (*head == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    while (current != NULL && current->fd != fd)
        current = current->next;
    if (current == NULL) {
        printf("Client non trouvé.\n");
        return;
    }
    close(current->fd);
    FD_CLR(current->fd, &s->client_fds);
    free(current);
}

int update_client_name(client_t **head, int fd, char *name)
{
    client_t *current = *head;

    if (current == NULL) {
        printf("La liste est vide.\n");
        return 0;
    }
    if (current->fd == fd) {
        if (current->log == false) {
            free(current->name);
            current->name = strdup(name);
            current->log = true;
            return 0;
        } else {
            write(current->fd, "Client already log\n", strlen("Client already log\n"));
            return 84;
        }
    }
    while (current->next != NULL) {
        if (current->next->fd == fd) {
            if (current->next->log == false) {
                free(current->next->name);
                current->next->name = strdup(name);
                current->next->log = true;
                return 0;
            } else {
                write(current->next->fd, "Client already log\n", strlen("Client already log\n"));
                return 84;
            }
        }
        current = current->next;
    }
    return 0;
}
