/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** my_strcat.c
*/

#include "server.h"

char *my_strcat(const char *str1, const char *str2)
{
    size_t length1 = 0;
    size_t length2 = 0;
    char *result = NULL;

    if (str1 == NULL || str2 == NULL)
        return NULL;
    length1 = strlen(str1);
    length2 = strlen(str2);
    result = malloc((length1 + length2 + 1) * sizeof(char));
    if (result == NULL)
        return NULL;
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}
