/*
** EPITECH PROJECT, 2024
** list.c
** File description:
** list initiation
*/

#include "server.h"

void init_server(server_t *s)
{
    s->exitProgram = false;
}

void init_list(server_t *s)
{
    s->clients = NULL;
}
