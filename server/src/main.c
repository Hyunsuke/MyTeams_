/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    server_t *s;

    if (ac == 2 && (strcmp(av[1], "-help") == 0)) {
        printhelp();
        return 0;
    }
    if (error_handling(ac, av) == 84)
        return 84;
    s = malloc(sizeof(server_t));
    s->port = atoi(av[1]);
    run_serv(s);
    return 0;
}
