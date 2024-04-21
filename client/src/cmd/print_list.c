/*
** EPITECH PROJECT, 2024
** print_list.c
** File description:
** print list
*/

#include "client.h"

void print_list_teams(client_t *client, char **commands)
{
    (void)commands;
    client_print_teams(client->team_uuid,
        client->team_name, client->team_description);
}

void print_list_channels(client_t *client, char **commands)
{
    (void)commands;
    client_print_channel(client->channel_uuid,
        client->channel_name, client->channel_description);
}

void print_list_threads(client_t *client, char **commands)
{
    (void)commands;
    client_print_thread(
        client->thread_uuid,
        client->user_uuid,
        client->thread_timestamp,
        client->thread_title,
        client->thread_body);
}

void print_list_replies(client_t *client, char **commands)
{
    (void)commands;
    client_thread_print_replies(
        client->thread_uuid,
        client->user_uuid,
        client->reply_timestamp,
        client->reply_body);
}
