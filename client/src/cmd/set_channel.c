/*
** EPITECH PROJECT, 2024
** set_channel.c
** File description:
** set channel info
*/

#include "client.h"

void set_channel_uuid(client_t *client, char **commands)
{
    client->channel_uuid = commands[1];
}

void set_channel_name(client_t *client, char **commands)
{
    client->channel_name = commands[1];
}

void set_channel_description(client_t *client, char **commands)
{
    client->channel_description = commands[1];
}
