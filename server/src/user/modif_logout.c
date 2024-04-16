/*
** EPITECH PROJECT, 2024
** modif_logout.c
** File description:
** modif when logout for user
*/

#include "server.h"

void check_client_down(user_t *current_user, server_t *s, int cli_fd,
    char *uuid_str)
{
    if (s->is_Ctrl_c == false) {
        send_uuid_to_client(cli_fd, uuid_str);
        usleep(1000);
        send_name_to_client(cli_fd, current_user->name);
        usleep(1000);
        send_logged_out_to_client(cli_fd);
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
        }
        current_user = current_user->next;
    }
}
