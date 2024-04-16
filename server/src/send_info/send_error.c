/*
** EPITECH PROJECT, 2024
** send_error.c
** File description:
** send error to client
*/

#include "server.h"

void send_unauthorized_to_client(int client_fd)
{
    char buffer[1024] = "UNAUTHORIZED";

    send(client_fd, buffer, strlen(buffer), 0);
}

void send_unknown_user_to_client(int client_fd)
{
    char buffer[1024] = "UNKNOWNUSER";

    send(client_fd, buffer, strlen(buffer), 0);
}
