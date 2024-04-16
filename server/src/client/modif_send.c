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

void receive_message(int client_fd, char *sender_uuid, char *message)
{
    send_message_to_client(client_fd, message);
    usleep(1000);
    send_uuid_to_client(client_fd, sender_uuid);
    usleep(1000);
    send_send_to_client(client_fd);
    usleep(1000);
}

void send_bad_uuid(int client_fd, char *uuid)
{
    send_uuid_to_client(client_fd, uuid);
    usleep(1000);
    send_unknown_user_to_client(client_fd);
    usleep(1000);
}
