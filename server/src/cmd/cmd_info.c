/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** cmd_info
*/

#include "server.h"

static int handle_info_intput(server_t *s, int client_fd)
{
    int nb_args = 0;

    if (check_and_handle_client_connection(s, client_fd) == 84)
        return 84;
    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 1) {
        write(client_fd, "Wrong number of argument for /info command\n",
            strlen("Wrong number of argument for /info command\n"));
        return 84;
    }
    return 0;
}

static int get_info_user(int client_fd, user_t *sender_user)
{
    char sender_user_uuid_str[37];
    char status_str[6];

    uuid_unparse(sender_user->uuid, sender_user_uuid_str);
    send(client_fd, my_strcat("UUID ", sender_user_uuid_str),
        strlen(sender_user_uuid_str) + 5, 0);
    usleep(1000);
    send(client_fd, my_strcat("NAME ", sender_user->name),
        strlen(sender_user->name) + 5, 0);
    usleep(1000);
    if (sender_user->log == 1)
        strcpy(status_str, "true");
    else
        strcpy(status_str, "false");
    send(client_fd, my_strcat("STATUS ", status_str),
        strlen(status_str) + 7, 0);
    usleep(1000);
    send(client_fd, "ONEUSER", 7, 0);
    usleep(10000);
    return 0;
}

static void send_team_info(int client_fd, char *team_uuid_str,
    team_t *current_team)
{
    send(client_fd, my_strcat("TEAM_UUID ", team_uuid_str),
        strlen(team_uuid_str) + 11, 0);
    usleep(1000);
    send(client_fd, my_strcat("TEAM_NAME ", current_team->name),
        strlen(current_team->name) + 11, 0);
    usleep(1000);
    send(client_fd, my_strcat("TEAM_DESCRIPTION ",
        current_team->description), strlen(current_team->description) +18, 0);
    usleep(10000);
    send(client_fd, "PRINT_INFO_TEAM", 15, 0);
    usleep(10000);
}

static int get_team_info(server_t *s,
    int client_fd, char *team_uuid_str)
{
    team_t *current_team = s->team;
    char current_team_uuid_str[37];

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, current_team_uuid_str);
        if (strcmp(current_team_uuid_str, team_uuid_str) == 0) {
            send_team_info(client_fd, current_team_uuid_str, current_team);
            return 0;
        }
        current_team = current_team->next;
    }
    write(client_fd, "Team not found\n", strlen("Team not found\n"));
    return 84;
}

static void send_channel_info(int client_fd,
    char *channel_uuid_str, channel_t *current_channel)
{
    send(client_fd, my_strcat("CHANNEL_UUID ", channel_uuid_str),
        strlen(channel_uuid_str) + 14, 0);
    usleep(1000);
    send(client_fd, my_strcat("CHANNEL_NAME ", current_channel->name),
        strlen(current_channel->name) + 14, 0);
    usleep(1000);
    send(client_fd,
        my_strcat("CHANNEL_DESCRIPTION ", current_channel->description),
        strlen(current_channel->description) + 23, 0);
    usleep(1000);
    send(client_fd, "PRINT_INFO_CHANNEL", 18, 0);
    usleep(1000);
}

static int get_channel_info(server_t *s,
    int client_fd, char *channel_uuid_str)
{
    channel_t *current_channel = s->team->channel;
    char current_channel_uuid_str[37];

    while (current_channel != NULL) {
        uuid_unparse(current_channel->uuid, current_channel_uuid_str);
        if (strcmp(current_channel_uuid_str, channel_uuid_str) == 0) {
            send_channel_info(client_fd,
            current_channel_uuid_str, current_channel);
            return 0;
        }
        current_channel = current_channel->next;
    }
    return 84;
}

static void send_thread_info(server_t *s, int client_fd, char *thread_uuid_str,
    thread_t *current_thread)
{
    char *uuid;
    char *timestamp_str = time_t_to_string(current_thread->time);

    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_UUID ", thread_uuid_str),
        strlen(thread_uuid_str) + 14, 0);
    usleep(1000);
    send(client_fd, my_strcat("THREAD_TITLE ", current_thread->title),
        strlen(current_thread->title) + 15, 0);
    usleep(1000);
    send(client_fd, my_strcat("THREAD_BODY ", current_thread->body),
        strlen(current_thread->body) + 14, 0);
    usleep(1000);
    send(client_fd, my_strcat("THREAD_TIMESTAMP ", timestamp_str),
        strlen(timestamp_str) + 19, 0);
    usleep(1000);
    send(client_fd, "PRINT_INFO_THREAD", 17, 0);
    usleep(1000);
}

static int get_thread_info(server_t *s,
    int client_fd, char *thread_uuid_str)
{
    thread_t *current_thread = s->team->channel->thread;
    char current_thread_uuid_str[37];

    while (current_thread != NULL) {
        uuid_unparse(current_thread->uuid, current_thread_uuid_str);
        if (strcmp(current_thread_uuid_str, thread_uuid_str) == 0) {
            send_thread_info(s, client_fd,
                current_thread_uuid_str, current_thread);
            return 0;
        }
        current_thread = current_thread->next;
    }
    return 84;
}

static int find_info_context(server_t *s, user_t *sender_user,
    int client_fd)
{
    char *type;
    char **context_tokens;

    context_tokens = my_str_to_word_array(sender_user->context, '/');
    type = get_type_of_create(s, client_fd);
    if (strcmp(type, "team") == 0)
        return get_info_user(client_fd, sender_user);
    if (strcmp(type, "channel") == 0)
        return get_team_info(s, client_fd, context_tokens[1]);
    if (strcmp(type, "thread") == 0)
        return get_channel_info(s, client_fd, context_tokens[2]);
    if (strcmp(type, "reply") == 0)
        return get_thread_info(s, client_fd, context_tokens[3]);
    return 0;
}

int info_cmd(server_t *s, int client_fd)
{
    user_t *sender_user = s->users;

    if (!s->save_struct->is_saving)
        return 1;
    if (handle_info_intput(s, client_fd) == 84)
        return 84;
    if (find_sender(s, client_fd, &sender_user) == 84)
        return 84;
    if (sender_user == NULL)
        return 84;
    find_info_context(s, sender_user, client_fd);
    return 1;
}
