/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** handle_args
*/

#include "server.h"

int isvalidport(char **av)
{
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (!isdigit(av[1][i]))
            return 84;
    }
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac == 2) {
        if (isvalidport(av) == 84) {
            printf("Error : Bad Port\n");
            return 84;
        }
        return 0;
    } else {
        printf("USAGE : ./myteams_server <port>\n");
        return 84;
    }
    return 0;
}
