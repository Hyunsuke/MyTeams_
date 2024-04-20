/*
** EPITECH PROJECT, 2024
** gestion_thread.c
** File description:
** gestion thread list
*/

#include "server.h"

char *time_t_to_string(time_t timestamp)
{
    struct tm *timeinfo;
    char *time_string = (char *)my_malloc(20 * sizeof(char));

    timeinfo = localtime(&timestamp);
    strftime(time_string, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_string;
}

void send_thread_created(server_t *s, int client_fd, time_t time_thread)
{
    char *uuid;
    char *timestamp_str = time_t_to_string(time_thread);

    uuid = get_user_uuid(s, client_fd);
    send(client_fd, my_strcat("THREAD_UUID ", s->uuid_thread), strlen(s->uuid_thread) + 13, 0);
    usleep(10000);
    send(client_fd, my_strcat("USER_UUID ", uuid), strlen(uuid) + 11, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_TIMESTAMP ", timestamp_str), strlen(timestamp_str) + 18, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_TITLE ", s->thread_title), strlen(s->thread_title) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("THREAD_BODY ", s->thread_body), strlen(s->thread_body) + 13, 0);
    usleep(10000);
    send(client_fd, "PRINT_THREAD_CREATED", 21, 0);
    usleep(10000);
}

thread_t *create_thread(server_t *s, int client_fd)
{
    thread_t *new_thread = my_malloc(sizeof(thread_t));

    (void)client_fd;
    if (new_thread != NULL) {
        uuid_generate(new_thread->uuid);
        uuid_unparse(new_thread->uuid, s->uuid_thread);
        new_thread->title = s->thread_title;
        new_thread->body = s->thread_body;
        new_thread->time = time(NULL);
        send_thread_created(s, client_fd, new_thread->time);
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

int define_new_thread(server_t *s, int client_fd, channel_t *current_channel)
{
    thread_t **thread_head;
    thread_t *current_thread;
    char *uuid_user = get_user_uuid(s, client_fd);
    thread_t *new_thread = create_thread(s, client_fd);

    if (strcmp(s->uuid_channel, s->parse_context[2]) == 0) {
        thread_head = &current_channel->thread;
        current_thread = *thread_head;
        set_new_thread(current_thread, new_thread, thread_head);
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
        if (define_new_thread(s, client_fd, current_channel) == 84) {
            return 84;
        }
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

void add_thread(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    char *error = "UNKNOWN_TEAM ";

    s->thread_title = remove_quotes(s->input_tab[1]);
    s->thread_body = remove_quotes(s->input_tab[2]);
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
