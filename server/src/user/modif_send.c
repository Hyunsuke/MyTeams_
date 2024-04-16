/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** modif_send
*/

#include "server.h"

int find_sender(server_t *s, int client_fd, user_t **sender_user)
{
    *sender_user = find_user_by_fd(s->clients, s->users, client_fd);
    if (*sender_user == NULL) {
        write(client_fd, "Sender user not found\n",
            strlen("Sender user not found\n"));
        return 84;
    }
    return 0;
}

int find_user(server_t *s, int client_fd, char *uuid, user_t **dest_user)
{
    *dest_user = find_user_by_uuid(s->users, uuid);
    if (*dest_user == NULL) {
        write(client_fd, "User not found\n", strlen("User not found\n"));
        return 84;
    }
    return 0;
}
