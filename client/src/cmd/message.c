/*
** EPITECH PROJECT, 2024
** message.c
** File description:
** message set
*/

#include "client.h"

void set_message(client_t *c, char **commands)
{
    c->message = commands[1];
}
