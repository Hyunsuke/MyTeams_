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
    {"STATUS", set_status},
    {"TIME", set_time},
    {"LOGGED", print_logged_in},
    {"NOLOGGED", print_logged_out},
    {"USERS", print_users},
    {"UNAUTHORIZED", print_unauthorized},
    {"SEND", print_send},
    {"MESSAGE", set_message},
    {"UNKNOWNUSER", print_unknown_user},
    {"ONEUSER", print_user},
    {"HELP", print_help},
    {"PRINTMESS", print_messages},
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
    write(1, buf, strlen(buf));
}

void handle_commands(client_t *c, char **commands, char *buffer)
{
    process_command(c, commands[0], commands, buffer);
}
