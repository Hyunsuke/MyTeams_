/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** modif_send
*/

#include "server.h"

int find_client(server_t *s, int client_fd,
    user_t *dest_user, client_t **dest_client)
{
    *dest_client = find_client_by_name(s->clients, dest_user->name);
    if (*dest_client == NULL) {
        write(client_fd, "Client not found\n", strlen("Client not found\n"));
        return 84;
    }
    return 0;
}
