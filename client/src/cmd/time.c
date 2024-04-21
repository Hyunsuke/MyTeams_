/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** time
*/

#include "client.h"

time_t get_time_from_string(const char *time_string)
{
    struct tm tm;
    time_t timestamp;

    memset(&tm, 0, sizeof(struct tm));
    if (strptime(time_string, "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return (time_t)-1;
    tm.tm_hour -= 1;
    if (tm.tm_hour < 0) {
        tm.tm_hour += 24;
        tm.tm_mday -= 1;
    }
    timestamp = mktime(&tm);
    if (timestamp == -1)
        return (time_t)-1;
    return timestamp;
}

time_t parse_time_string(const char *time_string)
{
    struct tm tm;
    time_t timestamp;

    memset(&tm, 0, sizeof(struct tm));
    if (strptime(time_string, "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return (time_t)-1;
    timestamp = mktime(&tm);
    if (timestamp == -1)
        return (time_t)-1;
    return timestamp;
}

void set_time(client_t *c, char **commands)
{
    c->timestamp = parse_time_string(commands[1]);
}
