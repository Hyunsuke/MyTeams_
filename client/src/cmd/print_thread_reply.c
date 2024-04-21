/*
** EPITECH PROJECT, 2024
** print_thread_reply.c
** File description:
** print thread reply
*/

#include "client.h"

void print_reply_received(client_t *client, char **commands)
{
    (void)commands;
    client_event_thread_reply_received(client->team_uuid, client->thread_uuid,
        client->user_uuid, client->reply_body);
}

void print_reply_created(client_t *client, char **commands)
{
    (void)commands;
    (void)client;
    client_print_reply_created(client->thread_uuid, client->user_uuid,
        client->reply_timestamp, client->reply_body);
}

void print_thread_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_thread_created(client->thread_uuid, client->user_uuid,
        client->thread_timestamp, client->thread_title, client->thread_body);
}

void print_thread_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_thread_created(client->thread_uuid, client->user_uuid,
        client->thread_timestamp, client->thread_title, client->thread_body);
}
