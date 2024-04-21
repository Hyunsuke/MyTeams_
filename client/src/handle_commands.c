/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "client.h"

time_t get_time_from_string(const char *time_string)
{
    struct tm tm;
    time_t timestamp;

    memset(&tm, 0, sizeof(struct tm));
    if (strptime(time_string, "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return (time_t)-1;
    tm.tm_hour -= 1;
    if (tm.tm_hour < 0) {
        tm.tm_hour += 24;
        tm.tm_mday -= 1;
    }
    timestamp = mktime(&tm);
    if (timestamp == -1)
        return (time_t)-1;
    return timestamp;
}

// Thread
void set_thread_uuid(client_t *client, char **commands)
{
    client->thread_uuid = commands[1];
}

void set_thread_timestamp(client_t *client, char **commands)
{
    (void)client;
    client->thread_timestamp = get_time_from_string(commands[1]);
}

void set_thread_title(client_t *client, char **commands)
{
    client->thread_title = commands[1];
}

void set_thread_body(client_t *client, char **commands)
{
    client->thread_body = commands[1];
}

// User
void set_user_uuid(client_t *client, char **commands)
{
    client->user_uuid = commands[1];
}

// Reply
void set_reply_body(client_t *client, char **commands)
{
    client->reply_body = commands[1];
}

void set_reply_timestamp(client_t *client, char **commands)
{
    (void)client;
    client->reply_timestamp = get_time_from_string(commands[1]);
}

// Print
void print_reply_received(client_t *client, char **commands)
{
    (void)commands;
    client_event_thread_reply_received(client->team_uuid, client->thread_uuid,
        client->user_uuid, client->reply_body);
}

void print_reply_created(client_t *client, char **commands)
{
    (void)commands;
    (void)client;
    client_print_reply_created(client->thread_uuid, client->user_uuid,
        client->reply_timestamp, client->reply_body);
}

void print_thread_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_thread_created(client->thread_uuid, client->user_uuid,
        client->thread_timestamp, client->thread_title, client->thread_body);
}

void print_thread_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_thread_created(client->thread_uuid, client->user_uuid,
        client->thread_timestamp, client->thread_title, client->thread_body);
}

void print_channel_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_channel_created(client->channel_uuid, client->channel_name,
        client->channel_description);
}

void print_channel_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_channel_created(client->channel_uuid, client->channel_name,
        client->channel_description);
}

void print_team_created(client_t *client, char **commands)
{
    (void)commands;
    client_print_team_created(client->team_uuid, client->team_name,
        client->team_description);
}

void print_team_event_created(client_t *client, char **commands)
{
    (void)commands;
    client_event_team_created(client->team_uuid, client->team_name,
        client->team_description);
}

// Team
void set_team_uuid(client_t *client, char **commands)
{
    client->team_uuid = commands[1];
}

void set_team_name(client_t *client, char **commands)
{
    client->team_name = commands[1];
}

void set_team_description(client_t *client, char **commands)
{
    client->team_description = commands[1];
}

// Channel
void set_channel_uuid(client_t *client, char **commands)
{
    client->channel_uuid = commands[1];
}

void set_channel_name(client_t *client, char **commands)
{
    client->channel_name = commands[1];
}

void set_channel_description(client_t *client, char **commands)
{
    client->channel_description = commands[1];
}

void print_client_already_exist(client_t *client, char **commands)
{
    (void)client;
    (void)commands;
    client_error_already_exist();
}

void print_subscribe_event(client_t *client, char **commands)
{
    (void)commands;
    client_print_subscribed(client->user_uuid, client->team_uuid);
}

void print_list_teams(client_t *client, char **commands)
{
    (void)commands;
    client_print_teams(client->team_uuid,
        client->team_name, client->team_description);
}

void print_list_channels(client_t *client, char **commands)
{
    (void)commands;
    client_print_channel(client->channel_uuid,
        client->channel_name, client->channel_description);
}

void print_list_threads(client_t *client, char **commands)
{
    (void)commands;
    client_print_thread(
        client->thread_uuid,
        client->user_uuid,
        client->thread_timestamp,
        client->thread_title,
        client->thread_body);
}

void print_list_replies(client_t *client, char **commands)
{
    (void)commands;
    client_thread_print_replies(
        client->thread_uuid,
        client->user_uuid,
        client->reply_timestamp,
        client->reply_body);
}

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
