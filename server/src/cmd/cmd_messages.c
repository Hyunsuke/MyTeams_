/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_messages
*/

#include "server.h"

int handle_messages_intputs(server_t *s, int client_fd)
{
    int nb_args = 0;

    if (check_and_handle_client_connection(s, client_fd) == 84)
        return 84;
    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(client_fd, "Wrong number of arguments for /messages command\n",
            strlen("Wrong number of arguments for /messages command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(client_fd, "user_uuid doesn't start or end with quotes\n",
            strlen("user_uuid doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

void send_info_messages_to_client(int client_fd,
    char *message, message_t *current_message)
{
    send_message_to_client(client_fd, message);
    usleep(1000);
    send_uuid_to_client(client_fd, current_message->sender_uuid);
    usleep(1000);
    send_timestamp_to_client(client_fd, current_message->timestamp);
    usleep(1000);
    send_message_list_to_client(client_fd);
    usleep(1000);
}

void give_message_linked_list_to_client(contact_t *current, int client_fd)
{
    message_t *current_message = current->content;

    if (current == NULL)
        return;
    while (current_message != NULL) {
        send_info_messages_to_client(client_fd,
            current_message->body, current_message);
        current_message = current_message->next;
    }
}

int process_messages_cmd(server_t *s, int client_fd)
{
    char *dest_uuid;
    user_t *sender_user = s->users;
    contact_t *current_contact = s->users->contact;

    dest_uuid = remove_quotes(s->input_tab[1]);
    if (find_sender(s, client_fd, &sender_user) == 84)
        return 84;
    if (sender_user == NULL) {
        write(client_fd, "User not found\n", strlen("User not found\n"));
        return 84;
    }
    current_contact = find_contact_by_uuid(sender_user->contact, dest_uuid);
    if (current_contact == NULL) {
        write(client_fd,
            "No existing discussion with the selected uuid\n", 46);
        return 84;
    }
    give_message_linked_list_to_client(current_contact, client_fd);
    return 0;
}

int messages_cmd(server_t *s, int client_fd)
{
    if (handle_messages_intputs(s, client_fd) == 84)
        return 84;
    return process_messages_cmd(s, client_fd);
}
