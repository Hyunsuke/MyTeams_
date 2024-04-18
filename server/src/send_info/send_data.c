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

void send_message_to_client(int client_fd, char *mess)
{
    char buffer[1024] = "MESSAGE ";

    strcat(buffer, mess);
    send(client_fd, buffer, strlen(buffer), 0);
}

void send_status_to_client(int client_fd, char *status)
{
    char buffer[1024] = "STATUS ";

    strcat(buffer, status);
    send(client_fd, buffer, strlen(buffer), 0);
}

void send_timestamp_to_client(int client_fd, time_t timestamp)
{
    char buffer[1024] = "TIME ";
    struct tm *timeinfo;
    char *time_string = (char *)malloc(20 * sizeof(char));

    if (time_string == NULL) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    timeinfo = localtime(&timestamp);
    strftime(time_string, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    strcat(buffer, time_string);
    send(client_fd, buffer, strlen(buffer), 0);
}
