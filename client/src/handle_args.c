/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** handle_args
*/

#include "client.h"

int isvalidport(char **av)
{
    for (int i = 0; av[2][i] != '\0'; i++) {
        if (!isdigit(av[2][i]))
            return 84;
    }
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac == 3) {
        if (isvalidport(av) == 84) {
            fprintf(stderr, "Error : Bad Port\n");
            return 84;
        }
        return 0;
    } else {
        fprintf(stderr, "USAGE : ./myteams_cli <ip> <port>\n");
        return 84;
    }
    return 0;
}
