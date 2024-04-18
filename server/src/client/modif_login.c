/*
** EPITECH PROJECT, 2024
** modif_login.c
** File description:
** modif client when log in
*/

#include "server.h"

int update_client(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            if (current_client->name == NULL) {
                current_client->log = true;
                free(current_client->name);
                current_client->name = s->name_login;
                break;
            } else {
                write(client_fd, "Client already log\n", 20);
                return 84;
            }
        }
        current_client = current_client->next;
    }
    return 0;
}
