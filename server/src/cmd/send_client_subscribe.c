/*
** EPITECH PROJECT, 2024
** send_client_subscribe.c
** File description:
** send elem subscribe
*/

#include "server.h"

void send_sub_to_subscribe(client_t *current_client, server_t *s,
    user_t *user_subscribe)
{
    if (current_client->name != NULL) {
        if (strcmp(user_subscribe->name, current_client->name) == 0) {
            send(current_client->fd, my_strcat("TEAM_UUID ", s->uuid_team),
                strlen(s->uuid_team) + 11, 0);
            usleep(10000);
            send(current_client->fd, my_strcat("USER_UUID ", s->uuid_user),
                strlen(s->uuid_user) + 11, 0);
            usleep(10000);
            send(current_client->fd, "PRINT_SUBSCRIBE_EVENT", 22, 0);
            usleep(10000);
        }
    }
}

void send_subscribe_to_subscribed(team_t *current_team, server_t *s)
{
    user_t **user_subscribe_head = &current_team->user;
    user_t *user_subscribe = *user_subscribe_head;
    client_t **client_head;
    client_t *current_client;

    while (user_subscribe != NULL) {
        client_head = &s->clients;
        current_client = *client_head;
        while (current_client != NULL) {
            send_sub_to_subscribe(current_client, s, user_subscribe);
            current_client = current_client->next;
        }
        user_subscribe = user_subscribe->next;
    }
}
