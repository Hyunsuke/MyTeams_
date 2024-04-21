/*
** EPITECH PROJECT, 2024
** gestion_channel.c
** File description:
** gestion_channel
*/

#include "server.h"

static void send_channel_to_subscribe(client_t *current_client, server_t *s,
    user_t *user_subscribe)
{
    if (current_client->name != NULL) {
        if (strcmp(user_subscribe->name, current_client->name) == 0) {
            send(current_client->fd,
                my_strcat("CHANNEL_UUID ", s->uuid_channel),
                    strlen(s->uuid_channel) + 14, 0);
            usleep(10000);
            send(current_client->fd,
                my_strcat("CHANNEL_NAME ", s->channel_name),
                    strlen(s->channel_name) + 14, 0);
            usleep(10000);
            send(current_client->fd,
                my_strcat("CHANNEL_DESCRIPTION ", s->channel_description),
                    strlen(s->channel_description) + 21, 0);
            usleep(10000);
            send(current_client->fd, "PRINT_CHANNEL_EVENT_CREATED", 28, 0);
            usleep(10000);
        }
    }
}

static void send_channel_created(team_t *current_team, server_t *s,
    int client_fd)
{
    user_t **user_subscribe_head = &current_team->user;
    user_t *user_subscribe = *user_subscribe_head;
    client_t **client_head;
    client_t *current_client;

    if (!s->save_struct->is_saving)
        return;
    while (user_subscribe != NULL) {
        client_head = &s->clients;
        current_client = *client_head;
        while (current_client != NULL) {
            send_channel_to_subscribe(current_client, s, user_subscribe);
            current_client = current_client->next;
        }
        user_subscribe = user_subscribe->next;
    }
    send(client_fd, "PRINT_CHANNEL_CREATED", 22, 0);
    usleep(10000);
}

channel_t *create_channel(server_t *s, int client_fd)
{
    channel_t *new_channel = my_malloc(sizeof(channel_t));

    s->channel_name = remove_quotes(s->input_tab[1]);
    s->channel_description = remove_quotes(s->input_tab[2]);
    (void)client_fd;
    if (new_channel != NULL) {
        if (s->save_struct->is_saving) {
            uuid_generate(new_channel->uuid);
            uuid_unparse(new_channel->uuid, s->uuid_channel);
        } else {
            strcpy(s->uuid_channel, s->save_struct->uuid);
            uuid_parse(s->save_struct->uuid, new_channel->uuid);
        }
        new_channel->name = s->channel_name;
        new_channel->description = s->channel_description;
        new_channel->thread = NULL;
        new_channel->next = NULL;
    }
    return new_channel;
}

void add_channel_to_team_list(server_t *s, team_t *current_team,
    channel_t **channel_head, channel_t *new_channel)
{
    channel_t *current_channel;

    if (*channel_head == NULL) {
        *channel_head = new_channel;
        if (s->save_struct->is_saving)
            send_channel_created(current_team, s, s->cli_fd);
    } else {
        current_channel = *channel_head;
        while (current_channel->next != NULL) {
            current_channel = current_channel->next;
        }
        current_channel->next = new_channel;
        if (s->save_struct->is_saving)
            send_channel_created(current_team, s, s->cli_fd);
    }
}

int check_if_good_team(server_t *s, team_t *current_team,
    const char *team_uuid, channel_t *new_channel)
{
    uuid_unparse(current_team->uuid, s->uuid_team);
    if (strcmp(s->uuid_team, team_uuid) == 0) {
        if (check_subscribe(current_team, s, s->cli_fd) == 84) {
            return 24;
        }
        add_channel_to_team_list(s, current_team, &current_team->channel,
            new_channel);
        if (s->save_struct->is_saving)
                server_event_channel_created(s->uuid_team,
                    s->uuid_channel, s->channel_name);
        return 0;
    }
    return 84;
}

int add_channel_to_team(server_t *s, channel_t *new_channel,
    const char *team_uuid)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    int status;

    while (current_team != NULL) {
        status = check_if_good_team(s, current_team, team_uuid, new_channel);
        if (status == 24)
            return 24;
        if (status == 0)
            return 0;
        current_team = current_team->next;
    }
    return 84;
}

static int do_channel_implementation(server_t *s, int client_fd,
    channel_t *new_channel, char *team_uuid)
{
    char *error = my_strcat("UNKNOWN_TEAM ", team_uuid);
    int status;

    status = add_channel_to_team(s, new_channel, team_uuid);
    if (status == 84) {
        if (s->save_struct->is_saving)
            send(client_fd, error, strlen(error), 0);
        usleep(10000);
        return 84;
    }
    if (status == 24) {
        if (s->save_struct->is_saving)
            send_unauthorized_to_client(client_fd);
        usleep(10000);
        return 84;
    }
    return 0;
}

int add_channel(server_t *s, int client_fd)
{
    channel_t *new_channel = create_channel(s, client_fd);
    char **parse_context = define_context(s, client_fd);
    char *team_uuid = parse_context[1];
    int status;

    s->cli_fd = client_fd;
    status = do_channel_implementation(s, client_fd, new_channel, team_uuid);
    if (status == 84)
        return 84;
    return 0;
}
