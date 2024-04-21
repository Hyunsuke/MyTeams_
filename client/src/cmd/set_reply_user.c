/*
** EPITECH PROJECT, 2024
** set_reply_user.c
** File description:
** set reply and user
*/

#include "client.h"

// User
void set_user_uuid(client_t *client, char **commands)
{
    client->user_uuid = commands[1];
}

// Reply
void set_reply_body(client_t *client, char **commands)
{
    client->reply_body = commands[1];
}

void set_reply_timestamp(client_t *client, char **commands)
{
    (void)client;
    client->reply_timestamp = get_time_from_string(commands[1]);
}
