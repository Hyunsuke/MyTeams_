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
    return 0;
}

int error_login(server_t *s)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(1, "Too many arguments for /login command\n",
            strlen("Too many arguments for /login command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "Name doesn't start or end with quotes\n",
            strlen("Name doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

int login_cmd(server_t *s, int client_fd)
{
    if (error_login(s) == 84)
        return 84;
    s->name_login = remove_quotes(s->input_tab[1]);
    s->isClientUpdated = true;
    return update_log(s, client_fd);
}
