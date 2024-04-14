/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** name.c
*/

#include "client.h"

void set_name(client_t *c, char **commands)
{
    c->name = commands[1];
}
