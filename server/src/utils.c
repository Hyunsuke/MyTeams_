/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** utils.c
*/

#include "server.h"

int connection_client(client_t *current_client, int client_fd)
{
    if (current_client->fd == client_fd) {
        if (current_client->name == NULL)
            return 84;
    }
    return 0;
}

int check_connection_client(client_t *current_client, int client_fd)
{
    while (current_client != NULL) {
        if (connection_client(current_client, client_fd) == 84) {
            return 84;
        }
        current_client = current_client->next;
    }
    return 0;
}

bool check_quotes(const char *str)
{
    if (str[0] == '"' && str[strlen(str) - 1] == '"')
        return true;
    else
        return false;
}

char *remove_quotes(const char *str)
{
    int length = strlen(str);
    char *new_str = malloc(length - 1);

    strncpy(new_str, str + 1, length - 2);
    new_str[length - 2] = '\0';
    return new_str;
}
