/*
** EPITECH PROJECT, 2024
** gestion_reply.c
** File description:
** gestion_reply.c
*/

#include "server.h"

void send_reply_received(server_t *s, int client_fd)
{
    char *uuid;

    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("TEAM_UUID ", s->uuid_team), strlen(s->uuid_team) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_UUID ", s->uuid_thread), strlen(s->uuid_thread) + 13, 0);
    usleep(10000);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("REPLY_BODY ", s->reply_body), strlen(s->reply_body) +12, 0);
    usleep(10000);
    send(client_fd, "PRINT_REPLY_RECEIVED", 21, 0);
    usleep(10000);
}

void send_reply_created(server_t *s, int client_fd, time_t time_reply)
{
    char *uuid;
    char *timestamp_str = time_t_to_string(time_reply);

    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("THREAD_UUID ", s->uuid_thread), strlen(s->uuid_thread) + 13, 0);
    usleep(10000);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("REPLY_TIMESTAMP ", timestamp_str), strlen(timestamp_str) + 17, 0);
    usleep(10000);
    send(client_fd, my_strcat("REPLY_BODY ", s->reply_body), strlen(s->reply_body) +12, 0);
    usleep(10000);
    send(client_fd, "PRINT_REPLY_CREATED", 21, 0);
    usleep(10000);
}

reply_t *create_reply(server_t *s, int client_fd)
{
    (void)client_fd;
    reply_t *new_reply = my_malloc(sizeof(reply_t));

    if (new_reply != NULL) {
        new_reply->body = s->reply_body;
        new_reply->time = time(NULL);
        send_reply_created(s, client_fd, new_reply->time);
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

int define_new_reply(server_t *s, int client_fd, thread_t *current_thread)
{
    reply_t **reply_head;
    reply_t *current_reply;
    reply_t *new_reply = create_reply(s, client_fd);
    char *uuid_user = get_user_uuid(s, client_fd);

    if (strcmp(s->uuid_thread, s->parse_context[3]) == 0) {
        reply_head = &current_thread->reply;
        current_reply = *reply_head;
        set_new_reply(current_reply, new_reply, reply_head);
        server_event_reply_created(s->uuid_thread, uuid_user,
            s->reply_body);
        //send reply à tous les clients subscribed
        return 84;
    }
    return 0;
}

static int find_right_thread(server_t *s, int client_fd,
    channel_t *current_channel)
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
        if (define_new_reply(s, client_fd, current_thread) == 84) {
            return 84;
        }
        current_thread = current_thread->next;
    }
    error = my_strcat(error, s->parse_context[3]);
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
        if (find_right_thread(s, client_fd, current_channel) == 84)
            return 84;
        current_channel = current_channel->next;
    }
    error = my_strcat(error, s->parse_context[2]);
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

void add_reply(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    char *error = "UNKNOWN_TEAM ";

    s->reply_body = remove_quotes(s->input_tab[1]);
    s->parse_context = define_context(s, client_fd);
    //NE PAS OUBLIER DE CHECK SI THREAD EXISTE DÉJÀ
    //NE PAS OUBLIER DE CHECK SI LE USER EST SUB A LA TEAM
    while (current_team != NULL) {
        if (find_right_team(s, client_fd, current_team) == 84)
            return;
        current_team = current_team->next;
    }
    error = my_strcat(error, s->parse_context[1]);
    send(client_fd, error, strlen(error), 0);
}
