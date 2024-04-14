/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** utils.c
*/

#include "server.h"

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
    printf("%s", new_str);
    return new_str;
}
