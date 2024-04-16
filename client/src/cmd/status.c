/*
** EPITECH PROJECT, 2024
** status.c
** File description:
** set status
*/

#include "client.h"

void set_status(client_t *c, char **commands)
{
    if (strcmp(commands[1], "true") == 0) {
        c->status = 1;
    } else if (strcmp(commands[1], "false") == 0) {
        c->status = 0;
    }
}
