/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** handle_args
*/

#include "client.h"

bool is_port_number_real(int port)
{
    return (port >= 1 && port <= 65535);
}

int isvalidport(char **av)
{
    for (int i = 0; av[2][i] != '\0'; i++) {
        if (!isdigit(av[2][i]))
            return 84;
    }
    if (!is_port_number_real(atoi(av[2])))
        return 84;
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac == 3) {
        if (isvalidport(av) == 84) {
            printf("Error : Bad Port\n");
            return 84;
        }
        return 0;
    } else {
        printf("USAGE : ./myteams_cli <ip> <port>\n");
        return 84;
    }
    return 0;
}
