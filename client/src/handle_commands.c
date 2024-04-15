/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "client.h"

command_handler_t commandHandlers[] = {
    {"UUID", set_uuid},
    {"NAME", set_name},
    {"LOGGED", print_logged_in},
    {"NOLOGGED", print_logged_out},
    {NULL, NULL}
};

void process_command(client_t *c, char *first_inp, char **commands, char *buf)
{
    for (int i = 0; commandHandlers[i].command != NULL; ++i) {
        if (strcmp(first_inp, commandHandlers[i].command) == 0) {
            commandHandlers[i].handler(c, commands);
            return;
        }
    }
    printf("%s", buf);
}

void handle_commands(client_t *c, char **commands, char *buffer)
{
    process_command(c, commands[0], commands, buffer);
}
