/*
** EPITECH PROJECT, 2024
** thread.c
** File description:
** thread gestion
*/

#include "client.h"

void set_thread_uuid(client_t *client, char **commands)
{
    client->thread_uuid = commands[1];
}

void set_thread_timestamp(client_t *client, char **commands)
{
    (void)client;
    client->thread_timestamp = get_time_from_string(commands[1]);
}

void set_thread_title(client_t *client, char **commands)
{
    client->thread_title = commands[1];
}

void set_thread_body(client_t *client, char **commands)
{
    client->thread_body = commands[1];
}
