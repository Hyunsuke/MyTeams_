/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** modif_list
*/

#include "server.h"

void send_list_teams_info(int client_fd, team_t *current_team, server_t *s)
{
    char current_team_uuid_str[37];

    if (!s->save_struct->is_saving)
        return;
    uuid_unparse(current_team->uuid, current_team_uuid_str);
    send(client_fd, my_strcat("TEAM_UUID ",
        current_team_uuid_str), strlen(current_team_uuid_str) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("TEAM_NAME ",
        current_team->name), strlen(current_team->name) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("TEAM_DESCRIPTION ",
        current_team->description), strlen(current_team->description) +18, 0);
    usleep(10000);
    send(client_fd, "PRINT_LIST_TEAMS", 16, 0);
    usleep(10000);
}

void send_list_channels_info(int client_fd,
    channel_t *current_channel, server_t *s)
{
    char current_channel_uuid_str[37];

    if (!s->save_struct->is_saving)
        return;
    uuid_unparse(current_channel->uuid, current_channel_uuid_str);
    send(client_fd, my_strcat("CHANNEL_UUID ",
        current_channel_uuid_str), strlen(current_channel_uuid_str) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_NAME ",
        current_channel->name), strlen(current_channel->name) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_DESCRIPTION ",
        current_channel->description),
        strlen(current_channel->description) + 21, 0);
    usleep(10000);
    send(client_fd, "PRINT_LIST_CHANNEL", 18, 0);
    usleep(10000);
}

void send_list_threads_info_bis(int client_fd,
    thread_t *current_thread, server_t *s)
{
    if (!s->save_struct->is_saving)
        return;
    send(client_fd, my_strcat("THREAD_TITLE ",
        current_thread->title), strlen(current_thread->title) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_BODY ",
        current_thread->body), strlen(current_thread->body) + 13, 0);
    usleep(10000);
    send(client_fd, "PRINT_LIST_THREAD", 17, 0);
    usleep(10000);
}

void send_list_threads_info(int client_fd, thread_t *current_thread,
    time_t time_thread, server_t *s)
{
    char current_thread_uuid_str[37];
    char *uuid;
    char *timestamp_str = time_t_to_string(time_thread);

    uuid_unparse(current_thread->uuid, current_thread_uuid_str);
    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("THREAD_UUID ",
        current_thread_uuid_str), strlen(current_thread_uuid_str) + 13, 0);
    usleep(10000);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_TIMESTAMP ",
        timestamp_str), strlen(timestamp_str) + 18, 0);
    usleep(10000);
    send_list_threads_info_bis(client_fd, current_thread, s);
}

void send_list_replies_info(int client_fd,
    reply_t *current_reply, thread_t *current_thread, server_t *s)
{
    char current_thread_uuid_str[37];
    char *uuid;
    char *timestamp_str = time_t_to_string(current_reply->time);

    uuid_unparse(current_thread->uuid, current_thread_uuid_str);
    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("THREAD_UUID ",
        current_thread_uuid_str), strlen(current_thread_uuid_str) + 13, 0);
    usleep(10000);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("REPLY_TIMESTAMP ",
        timestamp_str), strlen(timestamp_str) + 17, 0);
    usleep(10000);
    send(client_fd, my_strcat("REPLY_BODY ",
        current_reply->body), strlen(current_reply->body) + 12, 0);
    usleep(10000);
    send(client_fd, "PRINT_LIST_REPLY", 16, 0);
    usleep(10000);
}
