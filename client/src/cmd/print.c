/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** print.c
*/

#include "client.h"

void print_logged_in(client_t *client, char **commands)
{
    (void)commands;
    client_event_logged_in(client->uuid_str, client->name);
}

void print_logged_out(client_t *client, char **commands)
{
    (void)commands;
    client_event_logged_out(client->uuid_str, client->name);
}
