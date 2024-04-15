/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** send_infos.c
*/

#include "server.h"

void send_uuid_to_client(int client_fd, char *uuid_str)
{
    char buffer[1024] = "UUID ";

    strcat(buffer, uuid_str);
    send(client_fd, buffer, strlen(buffer), 0);
}

void send_name_to_client(int client_fd, char *name_str)
{
    char buffer[1024] = "NAME ";

    strcat(buffer, name_str);
    send(client_fd, buffer, strlen(buffer), 0);
}

void send_logged_in_to_client(int client_fd)
{
    char buffer[1024] = "LOGGED";

    send(client_fd, buffer, strlen(buffer), 0);
}

void send_logged_out_to_client(int client_fd)
{
    char buffer[1024] = "NOLOGGED";

    send(client_fd, buffer, strlen(buffer), 0);
}
