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
        uuid_generate(new_client->uuid);
        new_client->fd = fd;
        strcpy(new_client->name, "Not Defined");
        new_client->log = false;
        new_client->next = NULL;
    }
    return new_client;
}

void add_client(client_t **head, int fd)
{
    client_t *new_client = create_client(fd);
    client_t *current;

    if (new_client == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (*head == NULL) {
        *head = new_client;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_client;
    }
}

int search_fd(client_t *current, int fd)
{
    int indice = 0;

    while (current->next != NULL) {
        if (current->fd == fd) {
            return indice;
        }
        indice++;
        current = current->next;
    }
    printf("Client not found\n");
    return -1;
}

int find_client(client_t **head, int fd)
{
    client_t *current;

    if (*head == NULL) {
        return -1;
    } else {
        current = *head;
        return search_fd(current, fd);
    }
    return -1;
}

void remove_client(client_t **head, int fd)
{
    client_t *temp = *head;
    client_t *prev = NULL;

    if (*head == NULL) {
        return;
    }
    while (temp != NULL && temp->fd != fd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}
