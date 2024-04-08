/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    if (ac == 2 && (strcmp(av[1], "-help") == 0)) {
        printhelp();
        return 0;
    }
    if (error_handling(ac, av) == 84)
        return 84;
    return 0;
}
