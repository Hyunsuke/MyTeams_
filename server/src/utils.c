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
            dprintf(client_fd, "530 user not logged in\n");
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
    char *new_str = my_malloc(length - 1);

    strncpy(new_str, str + 1, length - 2);
    new_str[length - 2] = '\0';
    return new_str;
}

char *my_strdup(const char *src)
{
    size_t length = 0;
    char *dest = NULL;

    if (src == NULL)
        return NULL;
    length = strlen(src);
    dest = (char *)my_malloc((length + 1) * sizeof(char));
    if (dest == NULL)
        return NULL;
    strcpy(dest, src);
    return dest;
}
