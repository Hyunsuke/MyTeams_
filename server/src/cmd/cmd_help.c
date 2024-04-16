/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** cmd_help.c
*/

#include "server.h"

void help_cmd(server_t *s, int client_fd)
{
    (void)s;
    send(client_fd, "HELP", strlen("HELP"), 0);
}
