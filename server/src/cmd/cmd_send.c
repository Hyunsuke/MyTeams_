/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_send
*/

#include "server.h"

int handle_send_inputs(server_t *s)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 3) {
        write(1, "Wrong number of arguments for /send command\n",
            strlen("Wrong number of arguments for /send command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "user_uuid doesn't start or end with quotes\n",
            strlen("user_uuid doesn't start or end with quotes\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[2]) == false) {
        write(1, "The message doesn't start or end with quotes\n",
            strlen("The message doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

user_t *find_user_by_uuid(user_t *head, const char *uuid)
{
    user_t *current = head;
    char uuid_str[37];

    while (current != NULL) {
        uuid_unparse(current->uuid, uuid_str);
        if (strcmp(uuid_str, uuid) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void send_cmd(server_t *s, int client_fd)
{
    char *uuid;
    char *message;
    user_t *dest_user;

    if (handle_send_inputs(s) == 84)
        return;
    uuid = remove_quotes(s->input_tab[1]);
    message = remove_quotes(s->input_tab[2]);
    dest_user = find_user_by_uuid(s->users, uuid);
    if (dest_user == NULL) {
        write(client_fd, "User not found\n", strlen("User not found\n"));
        return;
    }
}
