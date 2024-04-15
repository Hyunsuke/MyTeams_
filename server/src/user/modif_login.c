/*
** EPITECH PROJECT, 2024
** modif_user.c
** File description:
** modif list with login
*/

#include "server.h"

user_t *right_place(user_t *new_current, char *name)
{
    while (new_current != NULL) {
        if (strcmp(new_current->name, name) == 0)
            break;
        new_current = new_current->next;
    }
    return new_current;
}

void update_cli(user_t **head, client_t **head_client, int cli_fd, char *name)
{
    user_t *new_current;
    char uuid_str[37];

    if (update_client_name(head_client, cli_fd, name) != 84) {
        add_user(head, name);
        new_current = *head;
        new_current = right_place(new_current, name);
        uuid_unparse(new_current->uuid, uuid_str);
        send_uuid_to_client(cli_fd, uuid_str);
        usleep(1000);
        send_name_to_client(cli_fd, new_current->name);
        usleep(1000);
        send_logged_in_to_client(cli_fd);
        server_event_user_created(uuid_str, new_current->name);
        server_event_user_logged_in(uuid_str);
    }
}

void check_alrlog(user_t *current, client_t **head_client, int cli_fd,
    char *name)
{
    char uuid_str[37];

    if (current->log) {
        dprintf(cli_fd, "User already assigned to a client\n");
    } else {
        if (update_client_name(head_client, cli_fd, name) != 84) {
            current->log = true;
            uuid_unparse(current->uuid, uuid_str);
            server_event_user_loaded(uuid_str, current->name);
            server_event_user_logged_in(uuid_str);
            send_uuid_to_client(cli_fd, uuid_str);
            usleep(1000);
            send_name_to_client(cli_fd, current->name);
            usleep(1000);
            send_logged_in_to_client(cli_fd);
        }
    }
}

int update_user_alrexist(user_t *current, client_t **head_client, int cli_fd,
    char *name)
{
    if (strcmp(current->name, name) == 0) {
        check_alrlog(current, head_client, cli_fd, name);
        return 84;
    }
    return 0;
}

void update_user(user_t **head, client_t **head_client, int cli_fd, char *name)
{
    user_t *current = *head;

    while (current != NULL) {
        if (update_user_alrexist(current, head_client, cli_fd, name) == 84)
            return;
        current = current->next;
    }
    update_cli(head, head_client, cli_fd, name);
}
