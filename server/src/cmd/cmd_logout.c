/*
** EPITECH PROJECT, 2024
** cmd_logout.c
** File description:
** commande logout
*/

#include "server.h"

void update_user_and_client_logout(server_t *s, user_t **user_head,
    client_t **client_head, int cli_fd)
{
    client_t *current_client = *client_head;
    user_t *current_user = *user_head;

    if (current_client == NULL) {
        printf("Liste Client vide.\n");
        return;
    }
    if (logout_client(current_client, cli_fd, s) == 84)
        return;
    logout_user(current_user, s, cli_fd);
}

int error_logout(server_t *s, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 1) {
        write(client_fd, "Too many arguments for /logout command\n",
            strlen("Too many arguments for /logout command\n"));
        return 84;
    }
    return 0;
}

void logout_cmd(server_t *s, int client_fd)
{
    s->is_Ctrl_c = false;
    if (error_logout(s, client_fd) == 84)
        return;
    update_user_and_client_logout(s, &s->users, &s->clients, client_fd);
}
