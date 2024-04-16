/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_send
*/

#include "server.h"

int handle_send_inputs(server_t *s, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 3) {
        write(client_fd, "Wrong number of arguments for /send command\n",
            strlen("Wrong number of arguments for /send command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(client_fd, "user_uuid doesn't start or end with quotes\n",
            strlen("user_uuid doesn't start or end with quotes\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[2]) == false) {
        write(client_fd, "The message doesn't start or end with quotes\n",
            strlen("The message doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

int check_and_handle_client_connection(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return 84;
    }
    return 0;
}

void send_private_message(user_t *sender_user, char *uuid,
    char *message, client_t *dest_client)
{
    char sender_uuid_str[37];

    uuid_unparse(sender_user->uuid, sender_uuid_str);
    server_event_private_message_sended(sender_uuid_str, uuid, message);
    receive_message(dest_client->fd, sender_uuid_str, message);
}

void execute_send_cmd(server_t *s, int client_fd, char *uuid, char *message)
{
    user_t *sender_user;
    user_t *dest_user;
    client_t *dest_client;

    if (find_sender(s, client_fd, &sender_user) == 84)
        return;
    if (find_user(s, client_fd, uuid, &dest_user) == 84) {
        return;
    }
    if (find_client(s, client_fd, dest_user, &dest_client) == 84)
        return;
    send_private_message(sender_user, uuid, message, dest_client);
}

void send_cmd(server_t *s, int client_fd)
{
    char *uuid;
    char *message;

    if (handle_send_inputs(s, client_fd) == 84)
        return;
    if (check_and_handle_client_connection(s, client_fd) == 84)
        return;
    uuid = remove_quotes(s->input_tab[1]);
    message = remove_quotes(s->input_tab[2]);
    execute_send_cmd(s, client_fd, uuid, message);
}
