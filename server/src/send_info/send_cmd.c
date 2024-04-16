/*
** EPITECH PROJECT, 2024
** send_cmd.c
** File description:
** send commande to client
*/

#include "server.h"

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

void send_users_to_client(int client_fd)
{
    char buffer[1024] = "USERS";

    send(client_fd, buffer, strlen(buffer), 0);
}

void send_unauthorized_to_client(int client_fd)
{
    char buffer[1024] = "UNAUTHORIZED";

    send(client_fd, buffer, strlen(buffer), 0);
}
