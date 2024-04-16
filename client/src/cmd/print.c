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

void print_send(client_t *client, char **commands)
{
    (void)commands;
    client_event_private_message_received(client->uuid_str, client->message);
}
