/*
** EPITECH PROJECT, 2024
** cmd_user.c
** File description:
** commande /users
*/

#include "server.h"

void send_user_infos(user_t *current_user, int client_fd)
{
    char uuid_str[37];
    char *log;

    log = (current_user->log <= 0) ? "false" : "true";
    uuid_unparse(current_user->uuid, uuid_str);
    send_uuid_to_client(client_fd, uuid_str);
    usleep(1000);
    send_name_to_client(client_fd, current_user->name);
    usleep(1000);
    send_status_to_client(client_fd, log);
    usleep(1000);
    send_users_to_client(client_fd);
    usleep(1000);
}

void send_user_list(user_t **user_head, client_t **client_head, int client_fd)
{
    user_t *current_user = *user_head;
    client_t *current_client = *client_head;

    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return;
    }
    if (current_user == NULL) {
        write(client_fd, "No user created\n", 17);
        return;
    }
    while (current_user != NULL) {
        send_user_infos(current_user, client_fd);
        current_user = current_user->next;
    }
}

int error_users(server_t *s, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 1) {
        write(client_fd, "Too many arguments for /users command\n",
            strlen("Too many arguments for /users command\n"));
        return 84;
    }
    return 0;
}

void users_cmd(server_t *s, int client_fd)
{
    if (error_users(s, client_fd) == 84)
        return;
    send_user_list(&s->users, &s->clients, client_fd);
}
