/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** send_cmd_bis
*/

#include "server.h"

void send_message_list_to_client(int client_fd)
{
    char buffer[1024] = "PRINTMESS";

    send(client_fd, buffer, strlen(buffer), 0);
}
