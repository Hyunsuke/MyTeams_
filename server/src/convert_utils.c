/*
** EPITECH PROJECT, 2024
** convert_utils.c
** File description:
** convert things
*/

#include "server.h"

char *time_t_to_string(time_t timestamp)
{
    struct tm *timeinfo;
    char *time_string = (char *)my_malloc(20 * sizeof(char));

    timeinfo = localtime(&timestamp);
    strftime(time_string, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_string;
}
