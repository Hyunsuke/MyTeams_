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
    {"/send", send_cmd},
    {"/messages", messages_cmd},
    {"/user", user_cmd},
    {"/help", help_cmd},
    {"/create", create_cmd},
    {"/use", use_cmd},
    {"/subscribe", subscribe_cmd},
    {"/list", list_cmd},
    {NULL, NULL}
};

int process_command(server_t *s, int client_fd, const char *command)
{
    for (int i = 0; commandHandlers[i].command != NULL; ++i) {
        if (strcmp(command, commandHandlers[i].command) == 0) {
            return commandHandlers[i].handler(s, client_fd);
        }
    }
    return 0;
}

int handle_commands(server_t *s, int client_fd)
{
    return process_command(s, client_fd, s->input_tab[0]);
}
