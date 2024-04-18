/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** main
*/

#include "client.h"

int main(int ac, char **av)
{
    client_t *client = my_malloc(sizeof(client_t));

    if (ac == 2 && (strcmp(av[1], "-help") == 0)) {
        printhelp();
        free(client);
        return 0;
    }
    if (error_handling(ac, av) == 84 ||
        create_client(client, av[1], atoi(av[2])) == 84) {
        free(client);
        return 84;
    }
    free(client);
    return 0;
}
