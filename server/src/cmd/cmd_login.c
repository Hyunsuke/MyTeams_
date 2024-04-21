/*
** EPITECH PROJECT, 2024
** cmd_login.c
** File description:
** login commande
*/

#include "server.h"

int update_log(server_t *s, int client_fd)
{
    if (update_client(s, client_fd) == 84) {
        return 84;
    }
    if (update_user_existing(s) == 84) {
        return 84;
    }
    update_user_not_exiting(s);
    dprintf(client_fd, "120 user logged successfully\n");
    return 0;
}

int error_login(server_t *s, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        dprintf(client_fd, "124 bad argument for /login command\n");
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        dprintf(client_fd, "124 bad argument for /login command\n");
        return 84;
    }
    return 0;
}

int login_cmd(server_t *s, int client_fd)
{
    if (error_login(s, client_fd) == 84)
        return 84;
    s->name_login = remove_quotes(s->input_tab[1]);
    s->isClientUpdated = true;
    return update_log(s, client_fd);
}
