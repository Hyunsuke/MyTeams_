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
    char *dest_uuid;
    // user_t *user;
    user_t *sender_user;
    message_t *current_message;
    send_to_t *current_send;

    if (handle_messages_intputs(s) == 84)
        return;
    dest_uuid = remove_quotes(s->input_tab[1]);
    write(1, "b", 1);
    if (find_sender(s, client_fd, &sender_user) == 84)
        return;
    write(1, "c", 1);
    if (sender_user == NULL) {
        write(client_fd, "User not found\n", strlen("User not found\n"));
        return;
    }
    write(1, "d", 1);
    printf("%s\n", sender_user->send->uuid);
    current_send = find_send_by_uuid(sender_user->send, dest_uuid);
    if (current_send == NULL) {
        write(1, "NUll", 4);
        return;
    }
    write(1, "e", 1);
    current_message = current_send->content;
    write(1, "f", 1);
    while (current_message != NULL) {
        write(1, "a", 1);
        //send toutes les infos
        dprintf(client_fd, "%s\n", current_message->body);
        current_message = current_message->next;
    }
}

