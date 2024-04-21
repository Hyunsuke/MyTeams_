/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** cmd_help.c
*/

#include "server.h"


char *list_commands(void)
{
    char *list_commands =
    "'/subscribed' ?[“team_uuid”] : list all subscribed teams "
    " or list all users subscribed to a team\n"
    "'/unsubscribe' [“team_uuid”] : unsubscribe from a team\n"
    "'/use' ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] :"
    " Sets the command context to a team/channel/thread\n"
    "'/create' : create a team, a channel,"
    " a thread or a reply based on the"
    " context you are currently in\n"
    "'/list' : list all teams, channels, threads or replies based"
    " on the context you are currently in\n"
    "'/info' : display details of the users, the selected team,"
    " the selected channel or the selected thread based on"
    " the context you are currently in\n";

    return list_commands;
}

int help_cmd(server_t *s, int client_fd)
{
    char *help_message =
    "Available commands:\n"
    "'/login' [“user_name”] : set the user_name used by client\n"
    "'/logout' : disconnect the client from the server\n"
    "'/users' : get the list of all users that exist on the domain\n"
    "'/user' [“user_uuid”] : get details about the requested user\n"
    "'/send' [“user_uuid”] [“message_body”] :"
    " send a message to specific user\n"
    "'/messages' [“user_uuid”] :"
    " list all messages exchanged with the specified user\n"
    "'/subscribe' [“team_uuid”] : subscribe to the events of a team and"
    " its sub directories"
    " (enable reception of all events from a team)\n";

    write(client_fd, help_message, strlen(help_message));
    write(client_fd, list_commands(), strlen(list_commands()));
    dprintf(client_fd, "170 list of commands retrieved successfully\n");
    (void)s;
    return 1;
}
