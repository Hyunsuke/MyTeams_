/*
** EPITECH PROJECT, 2024
** gestion_channel.c
** File description:
** gestion_channel
*/

#include "server.h"

void send_channel_created(server_t *s, int client_fd, char *name, char *desc)
{
    send(client_fd, my_strcat("CHANNEL_UUID ", s->uuid_channel), strlen(s->uuid_channel) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_NAME ", name), strlen(name) + 14, 0);
    usleep(10000);
    send(client_fd, my_strcat("CHANNEL_DESCRIPTION ", desc), strlen(desc) + 21, 0);
    usleep(10000);
    send(client_fd, "PRINT_CHANNEL_CREATED", strlen("PRINT_CHANNEL_CREATED"), 0);
    usleep(1000);
}

channel_t *create_channel(server_t *s, int client_fd, char *name,
    char *description)
{
    channel_t *new_channel = malloc(sizeof(channel_t));

    (void)client_fd;
    if (new_channel != NULL) {
        uuid_generate(new_channel->uuid);
        uuid_unparse(new_channel->uuid, s->uuid_channel);
        new_channel->name = name;
        new_channel->description = description;
        send_channel_created(s, client_fd, name, description);
        new_channel->thread = NULL;
        new_channel->next = NULL;
    }
    return new_channel;
}

void add_channel_to_team_list(channel_t **channel_head, channel_t *new_channel)
{
    channel_t *current_channel;

    if (*channel_head == NULL) {
        *channel_head = new_channel;
    } else {
        current_channel = *channel_head;
        while (current_channel->next != NULL) {
            current_channel = current_channel->next;
        }
        current_channel->next = new_channel;
    }
}

int add_channel_to_team(server_t *s, channel_t *new_channel,
    const char *team_uuid, const char *name)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, s->uuid_team);
        if (strcmp(s->uuid_team, team_uuid) == 0) {
            add_channel_to_team_list(&current_team->channel, new_channel);
            server_event_channel_created(s->uuid_team, s->uuid_channel, name);
            //send channel client à tous les clients subscribed
            return 0;
        }
        current_team = current_team->next;
    }
    return 84;
}

void add_channel(server_t *s, int client_fd)
{
    char *name = remove_quotes(s->input_tab[1]);
    char *description = remove_quotes(s->input_tab[2]);
    channel_t *new_channel = create_channel(s, client_fd, name, description);
    char **parse_context = define_context(s, client_fd);
    char *team_uuid = parse_context[1];
    char *error = my_strcat("UNKNOWN_TEAM ", team_uuid);

    //NE PAS OUBLIER DE CHECK SI LE USER EST SUBSCRIBE A LA TEAM
    if (add_channel_to_team(s, new_channel, team_uuid, name) == 84) {
        send(client_fd, error, strlen(error), 0);
    }
}
