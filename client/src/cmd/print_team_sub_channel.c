/*
** EPITECH PROJECT, 2024
** print_team_sub_channel.c
** File description:
** print team sub channel
*/

#include "client.h"

void print_channel_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_channel_created(client->channel_uuid, client->channel_name,
        client->channel_description);
}

void print_channel_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_channel_created(client->channel_uuid, client->channel_name,
        client->channel_description);
}

void print_team_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_team_created(client->team_uuid, client->team_name,
        client->team_description);
}

void print_team_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_team_created(client->team_uuid, client->team_name,
        client->team_description);
}

void print_subscribe_event(client_t *client, char **commands)
{
    (void)commands;
    client_print_subscribed(client->user_uuid, client->team_uuid);
}
