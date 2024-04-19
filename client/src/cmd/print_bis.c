/*
** EPITECH PROJECT, 2024
** print_bis.c
** File description:
** print_bis
*/

#include "client.h"

void print_unknown_user(client_t *client, char **commands)
{
    (void)commands;
    client_error_unknown_user(client->uuid_str);
}

void print_unknown_team(client_t *client, char **commands)
{
    (void)client;
    client_error_unknown_team(commands[1]);
}

void print_unknown_channel(client_t *client, char **commands)
{
    (void)client;
    client_error_unknown_channel(commands[1]);
}

void print_user(client_t *client, char **commands)
{
    (void)commands;
    client_print_user(client->uuid_str, client->name, client->status);
}

void print_help(client_t *c, char **commands)
{
    (void)c;
    (void)commands;
    printhelp();
}

void print_messages(client_t *c, char **commands)
{
    (void)commands;
    client_private_message_print_messages(
        c->uuid_str,
        c->timestamp,
        c->message);
}
