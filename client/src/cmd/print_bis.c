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

void print_user(client_t *client, char **commands)
{
    (void)commands;
    client_print_user(client->uuid_str, client->name, client->status);
}
