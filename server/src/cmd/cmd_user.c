/*
** EPITECH PROJECT, 2024
** cmd_user.c
** File description:
** cmd of user
*/

#include "server.h"

int author_cmd(client_t *current_client, int client_fd)
{
    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return 84;
    }
    return 0;
}

int send_to_client(user_t *current_user, int client_fd, char *clean_uuid)
{
    char *log;
    char uuid_str[37];

    uuid_unparse(current_user->uuid, uuid_str);
    if (strcmp(uuid_str, clean_uuid) == 0) {
        log = (current_user->log <= 0) ? "false" : "true";
        send_uuid_to_client(client_fd, uuid_str);
        usleep(1000);
        send_name_to_client(client_fd, current_user->name);
        usleep(1000);
        send_status_to_client(client_fd, log);
        usleep(1000);
        send_user_to_client(client_fd);
        usleep(1000);
        return 84;
    }
    return 0;
}

void send_user_info(user_t **user_head, client_t **client_head, int client_fd,
    char *clean_uuid)
{
    user_t *current_user = *user_head;
    client_t *current_client = *client_head;

    if (author_cmd(current_client, client_fd) == 84) {
        return;
    }
    while (current_user != NULL) {
        if (send_to_client(current_user, client_fd, clean_uuid) == 84)
            return;
        current_user = current_user->next;
    }
    send_uuid_to_client(client_fd, clean_uuid);
    usleep(1000);
    send_unknown_user_to_client(client_fd);
    usleep(1000);
}

int error_user(server_t *s)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(1, "Too many arguments for /user command\n",
            strlen("Too many arguments for /user command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "UUID doesn't start or end with quotes\n",
            strlen("UUID doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

int user_cmd(server_t *s, int client_fd)
{
    char *clean_uuid;

    if (error_user(s) == 84)
        return 84;
    clean_uuid = remove_quotes(s->input_tab[1]);
    if (s->save_struct->is_saving) {
        send_user_info(&s->users, &s->clients, client_fd, clean_uuid);
        dprintf(client_fd, "162 user details retrieved successfully\n");
    }
    return 1;
}
