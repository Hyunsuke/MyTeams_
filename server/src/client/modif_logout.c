/*
** EPITECH PROJECT, 2024
** modif_logout.c
** File description:
** modif when logout for cleint
*/

#include "server.h"

void assign_name(client_t *current_client, server_t *s)
{
    int i = 0;

    s->name_logout =
        my_malloc(sizeof(char) * (strlen(current_client->name) + 1));
    for (; current_client->name[i] != '\0'; i++)
        s->name_logout[i] = current_client->name[i];
    s->name_logout[i] = '\0';
}

int change_client_infos(client_t *current_client, int cli_fd, server_t *s)
{
    if (current_client->fd == cli_fd) {
        if (current_client->name != NULL) {
            assign_name(current_client, s);
            current_client->log = false;
            current_client->name = NULL;
            return 24;
        } else {
            send_unauthorized_to_client(cli_fd);
            usleep(1000);
            return 84;
        }
    }
    return 0;
}

int logout_client(client_t *current_client, int cli_fd, server_t *s)
{
    int check_infos;

    while (current_client != NULL) {
        check_infos = change_client_infos(current_client, cli_fd, s);
        if (check_infos == 84)
            return 84;
        if (check_infos == 24)
            break;
        current_client = current_client->next;
    }
    return 0;
}
