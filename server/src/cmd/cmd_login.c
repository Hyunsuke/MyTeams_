/*
** EPITECH PROJECT, 2024
** cmd_login.c
** File description:
** login commande
*/

#include "server.h"

void login_cmd(server_t *s, int client_fd)
{
    int nb_args = 0;
    char *correct_name;

    write(1, "Login detected\n", strlen("Login detected\n"));
    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(1, "Too many arguments for /login command\n",
            strlen("Too many arguments for /login command\n"));
        return;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "Name doesn't start or end with quotes\n",
            strlen("Name doesn't start or end with quotes\n"));
        return;
    }
    correct_name = remove_quotes(s->input_tab[1]);
    printf("%s\n", correct_name);
    update_user(&s->users, &s->clients, client_fd, correct_name);
    display_clients(s);
    display_users(s);
}
