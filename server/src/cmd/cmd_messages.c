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
        write(client_fd, "242 bad argument for /messages command\n",
            strlen("242 bad argument for /messages command\n"));
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

int give_message_list_to_cli(contact_t *current, int client_fd, server_t *s)
{
    message_t *current_message = current->content;

    if (current == NULL)
        return 1;
    while (current_message != NULL) {
        if (s->save_struct->is_saving)
            send_info_messages_to_client(client_fd,
                current_message->body, current_message);
        current_message = current_message->next;
    }
    return 1;
}

int process_messages_cmd(server_t *s, int client_fd)
{
    char *dest_uuid;
    user_t *sender_user = s->users;
    contact_t *current_contact = s->users->contact;

    dest_uuid = remove_quotes(s->input_tab[1]);
    if (find_sender(s, client_fd, &sender_user) == 84)
        return 84;
    if (sender_user == NULL)
        return 84;
    current_contact = find_contact_by_uuid(sender_user->contact, dest_uuid);
    if (current_contact == NULL) {
        write(client_fd,
            "244 no message exchange found with this user\n",
            strlen("244 no message exchange found with this user\n"));
        return 84;
    }
    write(client_fd,
            "240 list of messages retrieved successfully\n",
            strlen("240 list of messages retrieved successfully\n"));
    return give_message_list_to_cli(current_contact, client_fd, s);
}

int messages_cmd(server_t *s, int client_fd)
{
    if (handle_messages_intputs(s, client_fd) == 84)
        return 84;
    return process_messages_cmd(s, client_fd);
}
