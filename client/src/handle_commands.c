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
    {"UNKNOWN_TEAM", print_unknown_team},
    {"UNKNOWN_CHANNEL", print_unknown_channel},
    {"UNKNOWN_THREAD", print_unknown_thread},
    {"THREAD_UUID", set_thread_uuid},
    {"THREAD_TITLE", set_thread_title},
    {"THREAD_BODY", set_thread_body},
    {"THREAD_TIMESTAMP", set_thread_timestamp},
    {"USER_UUID", set_user_uuid},
    {"REPLY_BODY", set_reply_body},
    {"REPLY_TIMESTAMP", set_reply_timestamp},
    {"TEAM_UUID", set_team_uuid},
    {"TEAM_NAME", set_team_name},
    {"TEAM_DESCRIPTION", set_team_description},
    {"CHANNEL_UUID", set_channel_uuid},
    {"CHANNEL_NAME", set_channel_name},
    {"CHANNEL_DESCRIPTION", set_channel_description},
    {"PRINT_REPLY_RECEIVED", print_reply_received},
    {"PRINT_REPLY_CREATED", print_reply_created},
    {"PRINT_THREAD_CREATED", print_thread_created},
    {"PRINT_THREAD_EVENT_CREATED", print_thread_event_created},
    {"PRINT_CHANNEL_CREATED", print_channel_created},
    {"PRINT_CHANNEL_EVENT_CREATED", print_channel_event_created},
    {"PRINT_TEAM_CREATED", print_team_created},
    {"PRINT_TEAM_EVENT_CREATED", print_team_event_created},
    {"PRINT_CLIENT_EXIST", print_client_already_exist},
    {"PRINT_SUBSCRIBE_EVENT", print_subscribe_event},
    {"PRINT_LIST_TEAMS", print_list_teams},
    {"PRINT_LIST_CHANNEL", print_list_channels},
    {"PRINT_LIST_THREAD", print_list_threads},
    {"PRINT_LIST_REPLY", print_list_replies},
    {"PRINT_INFO_TEAM", print_info_team},
    {"PRINT_INFO_CHANNEL", print_info_channel},
    {"PRINT_INFO_THREAD", print_info_thread},
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
