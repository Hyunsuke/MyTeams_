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
