/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "server.h"

command_handler_t commandHandlers[] = {
    {"/login", login_cmd},
    {"/logout", logout_cmd},
    {"/users", users_cmd},
    {NULL, NULL}
};

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
