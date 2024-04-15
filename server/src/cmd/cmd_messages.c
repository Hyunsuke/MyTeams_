/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_messages
*/

#include "server.h"

int handle_messages_intputs(server_t *s)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(1, "Wrong number of arguments for /messages command\n",
            strlen("Wrong number of arguments for /messages command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "user_uuid doesn't start or end with quotes\n",
            strlen("user_uuid doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

void messages_cmd(server_t *s, int client_fd)
{
    char *uuid;

    if (handle_messages_intputs(s) == 84)
        return;
    uuid = remove_quotes(s->input_tab[1]);
}
