/*
** EPITECH PROJECT, 2024
** cmd_login.c
** File description:
** login commande
*/

#include "server.h"

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

void login_cmd(server_t *s, int client_fd)
{
    char *correct_name;

    if (error_login(s) == 84)
        return;
    correct_name = remove_quotes(s->input_tab[1]);
    update_user(&s->users, &s->clients, client_fd, correct_name);
}
