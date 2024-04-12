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
    if (find_user(&s->users, correct_name) == -1) {
        add_user(&s->users, correct_name);
        s->users[find_user(&s->users, correct_name)].log = true;
        s->clients[find_client(&s->clients, client_fd)].name = correct_name;
        printf("New user: %s\n", s->clients[find_client(&s->clients, client_fd)].name);
    } else if (s->users[find_user(&s->users, correct_name)].log == true) {
        write(1, "User already log\n", strlen("User already log\n"));
        return;
    } else {
        printf("bizarre");
        s->users[find_user(&s->users, correct_name)].log = true;
        s->clients[find_client(&s->clients, client_fd)].name = correct_name;
        printf("Client connected as: %s\n", s->clients[find_client(&s->clients, client_fd)].name);
    }
}
