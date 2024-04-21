/*
** EPITECH PROJECT, 2024
** gestion_reply.c
** File description:
** gestion_reply.c
*/

#include "server.h"

void send_reply_created(server_t *s, int client_fd, time_t time_reply,
    team_t *current_team)
{
    user_t **user_subscribe_head = &current_team->user;
    user_t *user_subscribe = *user_subscribe_head;
    char *timestamp_str = time_t_to_string(time_reply);
    char *uuid;
    client_t **client_head;
    client_t *current_client;

    if (!s->save_struct->is_saving)
        return;
    uuid = get_user_uuid(s, client_fd);
    while (user_subscribe != NULL) {
        client_head = &s->clients;
        current_client = *client_head;
        while (current_client != NULL) {
            if (current_client->name != NULL) {
                if (strcmp(user_subscribe->name, current_client->name) == 0) {
                    send(current_client->fd, my_strcat("THREAD_UUID ", s->uuid_thread), strlen(s->uuid_thread) + 13, 0);
                    usleep(10000);
                    send(current_client->fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
                    usleep(10000);
                    send(current_client->fd, my_strcat("REPLY_TIMESTAMP ", timestamp_str), strlen(timestamp_str) + 17, 0);
                    usleep(10000);
                    send(current_client->fd, my_strcat("REPLY_BODY ", s->reply_body), strlen(s->reply_body) + 12, 0);
                    usleep(10000);
                    send(current_client->fd, "PRINT_REPLY_RECEIVED", 21, 0);
                    usleep(10000);
                }
            }
            current_client = current_client->next;
        }
        user_subscribe = user_subscribe->next;
    }
    send(client_fd, "PRINT_REPLY_CREATED", 20, 0);
    usleep(10000);

}

reply_t *create_reply(server_t *s, int client_fd, team_t *current_team)
{
    reply_t *new_reply = my_malloc(sizeof(reply_t));

    if (new_reply != NULL) {
        new_reply->body = s->reply_body;
        new_reply->time = time(NULL);
        if (s->save_struct->is_saving)
            send_reply_created(s, client_fd, new_reply->time, current_team);
        new_reply->next = NULL;
    }
    return new_reply;
}

void set_new_reply(reply_t *current_reply, reply_t *new_reply,
    reply_t **reply_head)
{
    if (current_reply == NULL) {
        *reply_head = new_reply;
    } else {
        while (current_reply->next != NULL) {
            current_reply = current_reply->next;
        }
        current_reply->next = new_reply;
    }
}

int define_new_reply(server_t *s, int client_fd, thread_t *current_thread,
    team_t *current_team)
{
    reply_t **reply_head;
    reply_t *current_reply;
    reply_t *new_reply;
    char *uuid_user = get_user_uuid(s, client_fd);

    if (strcmp(s->uuid_thread, s->parse_context[3]) == 0) {
        reply_head = &current_thread->reply;
        current_reply = *reply_head;
        new_reply = create_reply(s, client_fd, current_team);
        set_new_reply(current_reply, new_reply, reply_head);
        server_event_reply_created(s->uuid_thread, uuid_user,
            s->reply_body);
        return 84;
    }
    return 0;
}

static int find_right_thread(server_t *s, int client_fd,
    channel_t *current_channel, team_t *current_team)
{
    thread_t **thread_head;
    thread_t *current_thread;
    char *error = "UNKNOWN_THREAD ";

    if (strcmp(s->uuid_channel, s->parse_context[2]) != 0)
        return 0;
    thread_head = &current_channel->thread;
    current_thread = *thread_head;
    while (current_thread != NULL) {
        uuid_unparse(current_thread->uuid, s->uuid_thread);
        if (define_new_reply(s, client_fd, current_thread, current_team) == 84) {
            return 84;
        }
        current_thread = current_thread->next;
    }
    error = my_strcat(error, s->parse_context[3]);
    if (s->save_struct->is_saving)
        send(client_fd, error, strlen(error), 0);
    return 84;
}

static int find_right_channel(server_t *s, int client_fd, team_t *current_team)
{
    channel_t **channel_head;
    channel_t *current_channel;
    char *error = "UNKNOWN_CHANNEL ";

    channel_head = &current_team->channel;
    current_channel = *channel_head;
    while (current_channel != NULL) {
        uuid_unparse(current_channel->uuid, s->uuid_channel);
        if (find_right_thread(s, client_fd, current_channel, current_team) == 84)
            return 84;
        current_channel = current_channel->next;
    }
    error = my_strcat(error, s->parse_context[2]);
    if (s->save_struct->is_saving)
        send(client_fd, error, strlen(error), 0);
    return 84;
}

static int find_right_team(server_t *s, int client_fd, team_t *current_team)
{
    uuid_unparse(current_team->uuid, s->uuid_team);
    if (strcmp(s->uuid_team, s->parse_context[1]) == 0) {
        if (check_subscribe(current_team, s, client_fd) == 84)
            return 84;
        if (find_right_channel(s, client_fd, current_team) == 84) {
            return 84;
        }
    }
    return 0;
}

int add_reply(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    char *error = "UNKNOWN_TEAM ";

    s->reply_body = remove_quotes(s->input_tab[1]);
    s->parse_context = define_context(s, client_fd);
    while (current_team != NULL) {
        if (find_right_team(s, client_fd, current_team) == 84)
            return 84;
        current_team = current_team->next;
    }
    error = my_strcat(error, s->parse_context[1]);
    if (s->save_struct->is_saving)
        send(client_fd, error, strlen(error), 0);
    return 0;
}
