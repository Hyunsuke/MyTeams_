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
        write(client_fd, "224 bad arguments for /send command\n",
            strlen("224 bad arguments for /send command\n"));
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
        if (s->save_struct->is_saving)
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

static void snd_contact(contact_t **contact, user_t *dest, char *uuid)
{
    (*contact) = find_contact_by_uuid(dest->contact, uuid);
    if ((*contact) == NULL) {
        add_contact(&dest->contact, uuid);
        (*contact) = find_contact_by_uuid(dest->contact, uuid);
    }
}

static void dupli_cntact(contact_t **cntact, user_t *send, char *uuid)
{
    (*cntact) = find_contact_by_uuid(send->contact, uuid);
    if ((*cntact) == NULL) {
        add_contact(&send->contact, uuid);
        (*cntact) = find_contact_by_uuid(send->contact, uuid);
    }
}

int execute_send_cmd(server_t *s, int client_fd, char *dest_uuid, char *msg)
{
    user_t *sender_user = s->users;
    user_t *dest_user = s->users;
    client_t *dest_client;
    time_t current_time = time(NULL);
    contact_t *contact = s->users->contact;
    contact_t *from_contact = s->users->contact;
    char sender_uuid_str[37];

    if (find_sender(s, client_fd, &sender_user) == 84 ||
        find_user(s, client_fd, dest_uuid, &dest_user) == 84 ||
        find_client(s, client_fd, dest_user, &dest_client) == 84)
        return 84;
    uuid_unparse(sender_user->uuid, sender_uuid_str);
    snd_contact(&contact, dest_user, sender_uuid_str);
    add_message(&contact->content, sender_uuid_str, msg, current_time);
    if (s->save_struct->is_saving)
        send_private_message(sender_user, dest_uuid, msg, dest_client);
    dupli_cntact(&from_contact, sender_user, dest_uuid);
    add_message(&from_contact->content, sender_uuid_str, msg, current_time);
    return 0;
}

int send_cmd(server_t *s, int client_fd)
{
    char *uuid;
    char *message;

    if (handle_send_inputs(s, client_fd) == 84)
        return 84;
    if (check_and_handle_client_connection(s, client_fd) == 84)
        return 84;
    uuid = remove_quotes(s->input_tab[1]);
    message = remove_quotes(s->input_tab[2]);
    if (execute_send_cmd(s, client_fd, uuid, message) == 84)
        return 0;
    write(client_fd, "202 message sent successfully\n",
        strlen("202 message sent successfully\n"));
    return 0;
}

//void execute_send_cmd(server_t *s, int client_fd, char *dest_uuid, char *msg)
// {
//     user_t *sender_user = s->users;
//     user_t *dest_user = s->users;
//     client_t *dest_client;
//     time_t current_time = time(NULL);
//     contact_t *contact = s->users->contact;
//     contact_t *from_contact = s->users->contact;
//     char sender_uuid_str[37];

//     if (find_sender(s, client_fd, &sender_user) == 84 ||
//         find_user(s, client_fd, dest_uuid, &dest_user) == 84 ||
//         find_client(s, client_fd, dest_user, &dest_client) == 84)
//         return;
//     uuid_unparse(sender_user->uuid, sender_uuid_str);
//     contact = find_contact_by_uuid(dest_user->contact, sender_uuid_str);
//     if (contact == NULL) {
//         add_contact(&dest_user->contact , sender_uuid_str);
//         contact = find_contact_by_uuid(dest_user->contact, sender_uuid_str);
//     }
//     add_message(&contact->content, dest_uuid, message, current_time);
//     send_private_message(sender_user, dest_uuid, message, dest_client);

//     from_contact = find_contact_by_uuid(sender_user->contact, dest_uuid);
//     if (from_contact == NULL) {
//         add_contact(&sender_user->contact , dest_uuid);
//     from_contact = find_contact_by_uuid(sender_user->contact, dest_uuid);
//     }
// add_message(&from_contact->content, sender_uuid_str, message, current_time);
// }
