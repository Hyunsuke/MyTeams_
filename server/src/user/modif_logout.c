/*
** EPITECH PROJECT, 2024
** modif_logout.c
** File description:
** modif when logout for user
*/

#include "server.h"

void close_client(server_t *s, client_t *current_client, int cli_fd)
{
    client_t **temp_head = &s->clients;

    if (current_client->fd == cli_fd) {
        remove_client(temp_head, cli_fd, s);
    }
}

void check_client_down(user_t *current_user, server_t *s, int cli_fd,
    char *uuid_str)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    while (current_client != NULL) {
        if (s->is_Ctrl_c == false) {
            send_uuid_to_client(current_client->fd, uuid_str);
            usleep(10000);
            send_name_to_client(current_client->fd, current_user->name);
            usleep(10000);
            send_logged_out_to_client(current_client->fd);
            usleep(10000);
            close_client(s, current_client, cli_fd);
        }
        current_client = current_client->next;
    }
}

void logout_user(user_t *current_user, server_t *s, int cli_fd)
{
    char uuid_str[37];

    while (current_user != NULL) {
        if (strcmp(current_user->name, s->name_logout) == 0) {
            current_user->log -= 1;
            uuid_unparse(current_user->uuid, uuid_str);
            server_event_user_logged_out(uuid_str);
            check_client_down(current_user, s, cli_fd, uuid_str);
            dprintf(cli_fd, "140 user successfully disconnected\n");
        }
        current_user = current_user->next;
    }
}
