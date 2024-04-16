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

void receive_message(int client_fd, char *sender_uuid, char *message)
{
    send_message_to_client(client_fd, message);
    usleep(1000);
    send_uuid_to_client(client_fd, sender_uuid);
    usleep(1000);
    send_send_to_client(client_fd);
    usleep(1000);
}

void send_bad_uuid(int client_fd, char *uuid)
{
    send_uuid_to_client(client_fd, uuid);
    usleep(1000);
}

void execute_send_cmd(server_t *s, int client_fd, char *uuid, char *message)
{
    char sender_uuid_str[37];
    user_t *sender_user;
    user_t *dest_user;
    client_t *dest_client;

    if (handle_send_inputs(s, client_fd) == 84)
        return;
    if (find_sender(s, client_fd, &sender_user) == 84)
        return;
    if (find_user(s, client_fd, uuid, &dest_user) == 84) {
        return;
    }
    if (find_client(s, client_fd, dest_user, &dest_client) == 84)
        return;
    uuid_unparse(sender_user->uuid, sender_uuid_str);
    server_event_private_message_sended(sender_uuid_str, uuid, message);
    receive_message(dest_client->fd, sender_uuid_str, message);
}

void send_cmd(server_t *s, int client_fd)
{
    char *uuid;
    char *message;

    uuid = remove_quotes(s->input_tab[1]);
    message = remove_quotes(s->input_tab[2]);
    execute_send_cmd(s, client_fd, uuid, message);
}
