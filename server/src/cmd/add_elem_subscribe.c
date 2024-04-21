/*
** EPITECH PROJECT, 2024
** add_elem_subscribe.c
** File description:
** add elem subscribe
*/

#include "server.h"

void set_values(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;
    char *name_user;

    while (current_client != NULL) {
        if (client_fd == current_client->fd) {
            name_user = current_client->name;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(name_user, current_user->name) == 0) {
            s->save_name = current_user->name;
            uuid_copy(s->save_uuid, current_user->uuid);
            return;
        }
        current_user = current_user->next;
    }
}

int user_alrdy_set(char *name, team_t *current_team)
{
    user_t **user_head = &current_team->user;
    user_t *user_subscribe = *user_head;

    while (user_subscribe != NULL) {
        if (strcmp(user_subscribe->name, name) == 0) {
            return 84;
        }
        user_subscribe = user_subscribe->next;
    }
    return 0;
}

user_t *cpy_user(server_t *s, int client_fd, team_t *current_team)
{
    user_t *new_user = my_malloc(sizeof(user_t));

    set_values(s, client_fd);
    if (user_alrdy_set(s->save_name, current_team) == 84) {
        return NULL;
    }
    if (new_user != NULL) {
        new_user->name = s->save_name;
        uuid_copy(new_user->uuid, s->save_uuid);
        new_user->next = NULL;
    }
    return new_user;
}

void add_user_elem(team_t *current_team, server_t *s, int client_fd)
{
    user_t *new_user = cpy_user(s, client_fd, current_team);
    user_t **user_head = &current_team->user;
    user_t *user_subscribe = *user_head;

    s->uuid_user = get_user_uuid(s, client_fd);
    if (new_user == NULL) {
        write(client_fd, "User already in list\n", 22);
        return;
    }
    if (user_subscribe == NULL) {
        *user_head = new_user;
    } else {
        while (user_subscribe->next != NULL) {
            user_subscribe = user_subscribe->next;
        }
        user_subscribe->next = new_user;
    }
    if (s->save_struct->is_saving)
        server_event_user_subscribed(s->uuid_team, s->uuid_user);
}
