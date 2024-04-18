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

void give_message_linked_list_to_client(contact_t *current, int client_fd)
{
    message_t *current_message = current->content;

    while (current_message != NULL) {
        dprintf(client_fd, "%s\n", current_message->body);
        current_message = current_message->next;
    }
}

void messages_cmd(server_t *s, int client_fd)
{
    char *dest_uuid;
    user_t *sender_user = s->users;
    contact_t *current_contact = s->users->contact;

    if (handle_messages_intputs(s) == 84)
        return;
    dest_uuid = remove_quotes(s->input_tab[1]);
    if (find_sender(s, client_fd, &sender_user) == 84)
        return;
    if (sender_user == NULL) {
        write(client_fd, "User not found\n", strlen("User not found\n"));
        return;
    }
    current_contact = find_contact_by_uuid(sender_user->contact, dest_uuid);
    if (current_contact == NULL) {
        write(client_fd, "No existing discussion with the selected uuid", 45);
        return;
    }
    give_message_linked_list_to_client(current_contact, client_fd);
}
