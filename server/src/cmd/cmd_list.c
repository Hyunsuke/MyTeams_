/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_list
*/

#include "server.h"

int handle_list_intput(server_t *s, int client_fd)
{
    int nb_args = 0;

    if (check_and_handle_client_connection(s, client_fd) == 84)
        return 84;
    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 1) {
        write(client_fd, "Wrong number of arguments for /list command\n",
            strlen("Wrong number of arguments for /list command\n"));
        return 84;
    }
    return 0;
}

static int list_teams(server_t *s, int client_fd)
{
    team_t *current_team = s->team;

    while (current_team != NULL) {
        send_list_teams_info(client_fd, current_team, s);
        current_team = current_team->next;
    }
    return 0;
}

static int send_channel(int client_fd, channel_t *current_channel, server_t *s)
{
    (void)client_fd;
    while (current_channel != NULL) {
        send_list_channels_info(client_fd, current_channel, s);
        current_channel = current_channel->next;
    }
    return 0;
}

static int list_channels_of_team(server_t *s,
    int client_fd, char *team_uuid_str)
{
    team_t *current_team = s->team;
    channel_t *current_channel;
    char current_team_uuid_str[37];

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, current_team_uuid_str);
        if (strcmp(current_team_uuid_str, team_uuid_str) == 0) {
            current_channel = current_team->channel;
            send_channel(client_fd, current_channel, s);
            return 0;
        }
        current_team = current_team->next;
    }
    write(client_fd, "Team not found\n", strlen("Team not found\n"));
    return 84;
}

static int send_thread(int client_fd, thread_t *current_thread, server_t *s)
{
    (void)client_fd;
    while (current_thread != NULL) {
        send_list_threads_info(client_fd,
            current_thread, current_thread->time, s);
        current_thread = current_thread->next;
    }
    return 0;
}

static int list_threads_of_channel(server_t *s,
    int client_fd, char *channel_uuid_str)
{
    channel_t *current_channel = s->team->channel;
    thread_t *current_thread;
    char current_channel_uuid_str[37];

    while (current_channel != NULL) {
        uuid_unparse(current_channel->uuid, current_channel_uuid_str);
        if (strcmp(current_channel_uuid_str, channel_uuid_str) == 0) {
            current_thread = current_channel->thread;
            send_thread(client_fd, current_thread, s);
            return 0;
        }
        current_channel = current_channel->next;
    }
    return 84;
}

static int send_reply(int client_fd,
    reply_t *current_reply, thread_t *current_thread, server_t *s)
{
    (void)client_fd;
    while (current_reply != NULL) {
        send_list_replies_info(client_fd, current_reply, current_thread, s);
        current_reply = current_reply->next;
    }
    return 0;
}

static int list_replies_of_thread(server_t *s,
    int client_fd, char *thread_uuid_str)
{
    thread_t *current_thread = s->team->channel->thread;
    reply_t *current_reply;
    char current_thread_uuid_str[37];

    while (current_thread != NULL) {
        uuid_unparse(current_thread->uuid, current_thread_uuid_str);
        if (strcmp(current_thread_uuid_str, thread_uuid_str) == 0) {
            current_reply = current_thread->reply;
            send_reply(client_fd, current_reply, current_thread, s);
            return 0;
        }
        current_thread = current_thread->next;
    }
    return 84;
}

int find_context(server_t *s, int client_fd, char *type, char **context_tokens)
{
    if (strcmp(type, "team") == 0)
        return list_teams(s, client_fd);
    if (strcmp(type, "channel") == 0)
        return list_channels_of_team(s, client_fd, context_tokens[1]);
    if (strcmp(type, "thread") == 0)
        return list_threads_of_channel(s, client_fd, context_tokens[2]);
    if (strcmp(type, "reply") == 0)
        return list_replies_of_thread(s, client_fd, context_tokens[3]);
    return 0;
}

int list_cmd(server_t *s, int client_fd)
{
    char *type;
    char **context_tokens;
    user_t *sender_user = s->users;

    if (handle_list_intput(s, client_fd) == 84)
        return 84;
    if (find_sender(s, client_fd, &sender_user) == 84)
        return 84;
    if (sender_user == NULL)
        return 84;
    context_tokens = my_str_to_word_array(sender_user->context, '/');
    type = get_type_of_create(s, client_fd);
    if (s->save_struct->is_saving) {
        find_context(s, client_fd, type, context_tokens);
        write(client_fd, "420 list retrieved successfully\n",
            strlen("420 list retrieved successfully\n"));
    }
    return 1;
}
