/*
** EPITECH PROJECT, 2024
** print_bis.c
** File description:
** print_bis
*/

#include "client.h"

void print_unknown_thread(client_t *client, char **commands)
{
    (void)client;
    client_error_unknown_thread(commands[1]);
}

void print_unknown_user(client_t *client, char **commands)
{
    (void)commands;
    client_error_unknown_user(client->uuid_str);
}

void print_client_already_exist(client_t *client, char **commands)
{
    (void)client;
    (void)commands;
    client_error_already_exist();
}
