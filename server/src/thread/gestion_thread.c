/*
** EPITECH PROJECT, 2024
** gestion_thread.c
** File description:
** gestion thread list
*/

#include "server.h"

static void send_independant_info(client_t *current_client, server_t *s)
{
    send(current_client->fd, my_strcat("THREAD_TITLE ", s->thread_title),
        strlen(s->thread_title) + 14, 0);
    usleep(10000);
    send(current_client->fd, my_strcat("THREAD_BODY ", s->thread_body),
        strlen(s->thread_body) + 13, 0);
    usleep(10000);
    send(current_client->fd, "PRINT_THREAD_EVENT_CREATED", 27, 0);
    usleep(10000);
}

static void use_fct_send_thread(client_t *current_client, server_t *s,
    user_t *user_subscribe, time_t time_thread)
{
    char *timestamp_str = time_t_to_string(time_thread);
    char *uuid = get_user_uuid(s, s->cli_fd);

    if (strcmp(user_subscribe->name, current_client->name) == 0) {
        send(current_client->fd, my_strcat("THREAD_UUID ", s->uuid_thread),
            strlen(s->uuid_thread) + 13, 0);
        usleep(10000);
        send(current_client->fd,
            my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
        usleep(10000);
        send(current_client->fd, my_strcat("THREAD_TIMESTAMP ", timestamp_str),
            strlen(timestamp_str) + 18, 0);
        usleep(10000);
        send_independant_info(current_client, s);
    }
}

static void send_thread_to_subscribe(client_t *current_client, server_t *s,
    user_t *user_subscribe, time_t time_thread)
{
    if (current_client->name != NULL) {
        use_fct_send_thread(current_client, s, user_subscribe, time_thread);
    }
}

void send_thread_created(server_t *s, team_t *current_team,
    int client_fd, time_t time_thread)
{
    user_t **user_subscribe_head = &current_team->user;
    user_t *user_subscribe = *user_subscribe_head;
    client_t **client_head;
    client_t *current_client;

    while (user_subscribe != NULL) {
        client_head = &s->clients;
        current_client = *client_head;
        while (current_client != NULL) {
            send_thread_to_subscribe(current_client, s, user_subscribe,
                time_thread);
            current_client = current_client->next;
        }
        user_subscribe = user_subscribe->next;
    }
    send(client_fd, "PRINT_THREAD_CREATED", 21, 0);
    usleep(10000);
}

thread_t *create_thread(server_t *s, int client_fd, team_t *current_team)
{
    thread_t *new_thread = my_malloc(sizeof(thread_t));

    (void)client_fd;
    if (new_thread != NULL) {
        uuid_generate(new_thread->uuid);
        uuid_unparse(new_thread->uuid, s->uuid_thread);
        new_thread->title = s->thread_title;
        new_thread->body = s->thread_body;
        new_thread->time = time(NULL);
        if (s->save_struct->is_saving)
            send_thread_created(s, current_team, client_fd, new_thread->time);
        new_thread->reply = NULL;
        new_thread->next = NULL;
    }
    return new_thread;
}

void set_new_thread(thread_t *current_thread, thread_t *new_thread,
    thread_t **thread_head)
{
    if (current_thread == NULL) {
        *thread_head = new_thread;
    } else {
        while (current_thread->next != NULL) {
            current_thread = current_thread->next;
        }
        current_thread->next = new_thread;
    }
}

int define_new_thread(server_t *s, int client_fd, channel_t *current_channel,
    team_t *current_team)
{
    thread_t **thread_head;
    thread_t *current_thread;
    char *uuid_user = get_user_uuid(s, client_fd);
    thread_t *new_thread;

    if (strcmp(s->uuid_channel, s->parse_context[2]) == 0) {
        thread_head = &current_channel->thread;
        current_thread = *thread_head;
        new_thread = create_thread(s, client_fd, current_team);
        set_new_thread(current_thread, new_thread, thread_head);
        if (s->save_struct->is_saving)
            server_event_thread_created(s->uuid_channel, s->uuid_thread,
            uuid_user, s->thread_title, s->thread_body);
        return 84;
    }
    return 0;
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
        if (define_new_thread(s, client_fd, current_channel,
            current_team) == 84) {
            return 84;
        }
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

int add_thread(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    char *error = "UNKNOWN_TEAM ";

    s->thread_title = remove_quotes(s->input_tab[1]);
    s->thread_body = remove_quotes(s->input_tab[2]);
    s->parse_context = define_context(s, client_fd);
    s->cli_fd = client_fd;
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
