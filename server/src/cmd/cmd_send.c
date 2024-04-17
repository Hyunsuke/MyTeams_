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


send_to_t *create_send(char *uuid)
{
    send_to_t *new_sender = malloc(sizeof(send_to_t));

    if (new_sender != NULL) {
        new_sender->uuid = strdup(uuid);
        new_sender->content = NULL;
        new_sender->next = NULL;

    }
    return new_sender;
}

void add_send(send_to_t **head, char *uuid)
{
    send_to_t *new_sender = create_send(uuid);
    send_to_t *current = *head;

    if (new_sender == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_sender;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_sender;
    }
}

send_to_t *find_send_by_uuid(send_to_t *head, char *uuid)
{
    send_to_t *current = head;

    while (current != NULL) {
        if (strcmp(current->uuid, uuid) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

message_t *create_message(char *uuid, char *message, time_t timestamp)
{
    message_t *new_message = malloc(sizeof(message_t));

    if (new_message != NULL) {
        new_message->sender_uuid = uuid;
        new_message->timestamp = timestamp;
        new_message->body = message;
        new_message->next = NULL;
    }
    return new_message;
}

void add_message(message_t **head, char *uuid, char *message, time_t timestamp)
{
    message_t *new_message = create_message(uuid, message, timestamp);
    message_t *current = *head;
    if (new_message == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_message;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_message;
    }
}

void send_private_message(user_t *sender_user, char *uuid,
    char *message, client_t *dest_client)
{
    char sender_uuid_str[37];

    uuid_unparse(sender_user->uuid, sender_uuid_str);
    server_event_private_message_sended(sender_uuid_str, uuid, message);
    receive_message(dest_client->fd, sender_uuid_str, message);
}

void execute_send_cmd(server_t *s, int client_fd, char *dest_uuid, char *message)
{
    user_t *sender_user;
    user_t *dest_user;
    client_t *dest_client;
    time_t current_time = time(NULL);
    send_to_t *contact;
    char sender_uuid_str[37];

    if (find_sender(s, client_fd, &sender_user) == 84)
        return;

    if (find_user(s, client_fd, dest_uuid, &dest_user) == 84) {
        return;
    }

    if (find_client(s, client_fd, dest_user, &dest_client) == 84)
        return;
    contact = find_send_by_uuid(dest_user->send, dest_uuid);
    if (contact == NULL) {
        add_send(&dest_user->send , dest_uuid);
        contact = find_send_by_uuid(dest_user->send, dest_uuid);
    }
    add_message(&contact->content, dest_uuid, message, current_time);
    send_private_message(sender_user, dest_uuid, message, dest_client);

    uuid_unparse(sender_user->uuid, sender_uuid_str);
    contact = find_send_by_uuid(sender_user->send, sender_uuid_str);
    if (contact == NULL) {
        add_send(&sender_user->send , sender_uuid_str);
        contact = find_send_by_uuid(sender_user->send, sender_uuid_str);
    }
    add_message(&contact->content, sender_uuid_str, message, current_time);
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
