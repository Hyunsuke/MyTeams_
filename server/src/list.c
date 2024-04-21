/*
** EPITECH PROJECT, 2024
** list.c
** File description:
** list initiation
*/

#include "server.h"

void init_save(server_t *s)
{
    s->save_struct = my_malloc(sizeof(save_t));
    s->save_struct->uuid = NULL;
    s->save_struct->is_saving = false;
    s->save_struct->buffer = NULL;
    s->save_struct->is_uuid_there = false;
}

void init_server(server_t *s)
{
    s->exitProgram = false;
}

void init_list(server_t *s)
{
    init_server(s);
    init_save(s);
    s->clients = NULL;
    s->users = NULL;
    s->team = NULL;
    s->isClientUpdated = false;
}
