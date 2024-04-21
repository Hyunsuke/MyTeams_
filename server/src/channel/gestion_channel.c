/*
** EPITECH PROJECT, 2024
** gestion_channel.c
** File description:
** gestion_channel
*/

#include "server.h"

void send_channel_created(server_t *s, int client_fd)
{
    send(client_fd, my_strcat("CHANNEL_UUID ", s->uuid_channel), strlen(s->uuid_channel) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_NAME ", s->channel_name), strlen(s->channel_name) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_DESCRIPTION ", s->channel_description), strlen(s->channel_description) + 21, 0);
    usleep(10000);
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
        uuid_generate(new_channel->uuid);
        uuid_unparse(new_channel->uuid, s->uuid_channel);
        new_channel->name = s->channel_name;
        new_channel->description = s->channel_description;
        new_channel->thread = NULL;
        new_channel->next = NULL;
    }
    return new_channel;
}

void add_channel_to_team_list(server_t *s, channel_t **channel_head, channel_t *new_channel)
{
    channel_t *current_channel;

    if (*channel_head == NULL) {
        *channel_head = new_channel;
        send_channel_created(s, s->cli_fd);
    } else {
        current_channel = *channel_head;
        while (current_channel->next != NULL) {
            current_channel = current_channel->next;
        }
        current_channel->next = new_channel;
        send_channel_created(s, s->cli_fd);
    }
}

int add_channel_to_team(server_t *s, channel_t *new_channel,
    const char *team_uuid)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, s->uuid_team);
        if (strcmp(s->uuid_team, team_uuid) == 0) {
            if (check_subscribe(current_team, s, s->cli_fd) == 84) {
                return 24;
            }
            add_channel_to_team_list(s, &current_team->channel, new_channel);
            server_event_channel_created(s->uuid_team, s->uuid_channel, s->channel_name);
            return 0;
        }
        current_team = current_team->next;
    }
    return 84;
}

void add_channel(server_t *s, int client_fd)
{
    channel_t *new_channel = create_channel(s, client_fd);
    char **parse_context = define_context(s, client_fd);
    char *team_uuid = parse_context[1];
    char *error = my_strcat("UNKNOWN_TEAM ", team_uuid);

    s->cli_fd = client_fd;
    int status = add_channel_to_team(s, new_channel, team_uuid);
    if (status == 84) {
        send(client_fd, error, strlen(error), 0);
        usleep(10000);
        return;
    } else if (status == 24) {
        send_unauthorized_to_client(client_fd);
        usleep(10000);
    }
}
