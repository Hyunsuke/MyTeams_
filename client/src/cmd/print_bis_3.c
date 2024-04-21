/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** print_bis_3
*/

#include "client.h"

void print_info_team(client_t *client, char **commands)
{
    (void)commands;
    client_print_team(
        client->team_uuid,
        client->team_name,
        client->team_description);
}

void print_info_channel(client_t *client, char **commands)
{
    (void)commands;
    client_print_channel(
        client->channel_uuid,
        client->channel_name,
        client->channel_description);
}

void print_info_thread(client_t *client, char **commands)
{
    (void)commands;
    client_print_thread(
        client->thread_uuid,
        client->user_uuid,
        client->thread_timestamp,
        client->thread_title,
        client->thread_body);
}
