/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** login.c
*/

#include "client.h"

void set_uuid(client_t *c, char **commands)
{
    c->uuid_str = commands[1];
}
