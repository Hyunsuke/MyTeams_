/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "server.h"
command_handler_t commandHandlers[] = {
    {"/login", handle_login},
    {"COMMAND2\n", handle_command2},
    {NULL, NULL}
};

void handle_login(server_t *s, int client_fd)
{
    printf("bonjour\n");
    (void)client_fd;
    (void)s;
}

void handle_command2(server_t *s, int client_fd)
{
    (void)client_fd;
    (void)s;
}

void process_command(server_t *s, int client_fd, const char *command)
{
    for (int i = 0; commandHandlers[i].command != NULL; ++i) {
        if (strcmp(command, commandHandlers[i].command) == 0) {
            commandHandlers[i].handler(s, client_fd);
            return;
        }
    }
}

void handle_commands(server_t *s, int client_fd)
{
    process_command(s, client_fd, s->input_tab[0]);
}
