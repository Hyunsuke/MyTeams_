/*
** EPITECH PROJECT, 2024
** modif_user.c
** File description:
** modif list with login
*/

#include "server.h"

void send_from_user_existence(user_t *current_user,
    client_t *new_current_client, char *uuid)
{
    if (new_current_client->name != NULL) {
        send_uuid_to_client(new_current_client->fd, uuid);
        usleep(10000);
        send_name_to_client(new_current_client->fd, current_user->name);
        usleep(10000);
        send_logged_in_to_client(new_current_client->fd);
        usleep(10000);
    }
}

int check_user_existence(server_t *s, user_t *current_user,
    client_t *new_current_client)
{
    char uuid[37];

    if (strcmp(current_user->name, s->name_login) == 0) {
        current_user->log += 1;
        uuid_unparse(current_user->uuid, uuid);
        while (new_current_client != NULL) {
            if (s->save_struct->is_uuid_there)
            send_from_user_existence(current_user, new_current_client, uuid);
            new_current_client = new_current_client->next;
        }
        if (s->save_struct->is_uuid_there)
            server_event_user_logged_in(uuid);
        return 84;
    }
    return 0;
}

int update_user_existing(server_t *s)
{
    client_t **new_client_head = &s->clients;
    client_t *new_current_client = *new_client_head;
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;

    while (current_user != NULL) {
        if (check_user_existence(s, current_user, new_current_client) == 84) {
            return 84;
        }
        current_user = current_user->next;
    }
    return 0;
}

static void send_from_check_pos(user_t *new_current_user,
    client_t *new_current_client, char *uuid, server_t *s)
{
    if (new_current_client->name != NULL && s->save_struct->is_saving) {
        send_uuid_to_client(new_current_client->fd, uuid);
        usleep(10000);
        send_name_to_client(new_current_client->fd, new_current_user->name);
        usleep(10000);
        send_logged_in_to_client(new_current_client->fd);
        usleep(10000);
    }
}

int check_position_user(server_t *s, client_t *new_current_client,
    user_t *new_current_user)
{
    char uuid[37];

    if (strcmp(new_current_user->name, s->name_login) == 0) {
        uuid_unparse(new_current_user->uuid, uuid);
        while (new_current_client != NULL) {
            if (s->save_struct->is_saving)
            send_from_check_pos(new_current_user, new_current_client, uuid, s);
            new_current_client = new_current_client->next;
        }
        if (s->save_struct->is_saving) {
        server_event_user_created(uuid, new_current_user->name);
        server_event_user_logged_in(uuid);
        }
        return 84;
    }
    return 0;
}

void update_user_not_exiting(server_t *s)
{
    client_t **new_client_head = &s->clients;
    client_t *new_current_client = *new_client_head;
    user_t **new_user_head = &s->users;
    user_t *new_current_user;
    char uuid[37];

    add_user(s, new_user_head, s->name_login);
    new_current_user = *new_user_head;
    while (new_current_user != NULL) {
        if (check_position_user(s, new_current_client,
            new_current_user) == 84) {
            uuid_unparse(new_current_user->uuid, uuid);
            s->save_struct->buffer = my_strcat(s->save_struct->buffer, "\e");
            s->save_struct->buffer = my_strcat(s->save_struct->buffer, uuid);
            return;
        }
        new_current_user = new_current_user->next;
    }
}
