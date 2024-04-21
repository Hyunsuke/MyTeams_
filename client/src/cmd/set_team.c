/*
** EPITECH PROJECT, 2024
** set_team.c
** File description:
** set team
*/

#include "client.h"

void set_team_uuid(client_t *client, char **commands)
{
    client->team_uuid = commands[1];
}

void set_team_name(client_t *client, char **commands)
{
    client->team_name = commands[1];
}

void set_team_description(client_t *client, char **commands)
{
    client->team_description = commands[1];
}
