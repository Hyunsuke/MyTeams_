/*
** EPITECH PROJECT, 2024
** getsion_team.c
** File description:
** gestion of list team
*/

#include "server.h"

void send_team_created(server_t *s, int client_fd, char *name, char *desc)
{
    client_t **head = &s->clients;
    client_t *current_client = *head;
    while (current_client != NULL) {
        if (current_client->name != NULL) {
            send(current_client->fd, my_strcat("TEAM_UUID ", s->uuid_team), strlen(s->uuid_team) + 11, 0);
            usleep(10000);
            send(current_client->fd, my_strcat("TEAM_NAME ", name), strlen(name) + 11, 0);
            usleep(10000);
            send(current_client->fd, my_strcat("TEAM_DESCRIPTION ", desc), strlen(desc) +18, 0);
            usleep(10000);
            send(current_client->fd, "PRINT_TEAM_EVENT_CREATED", 25, 0);
            usleep(10000);
        }
        current_client = current_client->next;
    }
    send(client_fd, "PRINT_TEAM_CREATED", 19, 0);
    usleep(10000);
}

team_t *create_team(server_t *s, int client_fd, char *name, char *description)
{
    team_t *new_team = my_malloc(sizeof(team_t));

    (void)client_fd;
    if (new_team != NULL) {
        uuid_generate(new_team->uuid);
        uuid_unparse(new_team->uuid, s->uuid_team);
        new_team->name = name;
        new_team->description = description;
        send_team_created(s, client_fd, name, description);
        new_team->user = NULL;
        new_team->channel = NULL;
        new_team->next = NULL;
    }
    return new_team;
}

static int check_team(server_t *s, char *name)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        if (strcmp(current_team->name, name) == 0) {
            return 84;
        }
        current_team = current_team->next;
    }
    return 0;
}

char *search_uuid(server_t *s, char *name_user)
{
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;
    char *uuid_str = (char *)my_malloc((37 + 1) * sizeof(char));

    while (current_user != NULL) {
        if (strcmp(current_user->name, name_user) == 0) {
            uuid_unparse(current_user->uuid, uuid_str);
            break;
        }
        current_user = current_user->next;
    }
    return uuid_str;
}

char *get_user_uuid(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;
    char *name_user;
    char *uuid_str;

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            name_user = current_client->name;
            break;
        }
        current_client = current_client->next;
    }
    uuid_str = search_uuid(s, name_user);
    return uuid_str;
}

void update_team_list(server_t *s, int client_fd, char *name,
    char *description)
{
    team_t **team_head = &s->team;
    team_t *new_team = create_team(s, client_fd, name, description);
    team_t *current_team = *team_head;

    if (current_team == NULL) {
        *team_head = new_team;
    } else {
        while (current_team->next != NULL) {
            current_team = current_team->next;
        }
        current_team->next = new_team;
    }
}

void add_team(server_t *s, int client_fd)
{
    char *name = remove_quotes(s->input_tab[1]);
    char *description = remove_quotes(s->input_tab[2]);
    char *uuid_str = get_user_uuid(s, client_fd);

    if (check_team(s, name) == 84) {
        send(client_fd, "PRINT_CLIENT_EXIST", 19, 0);
        usleep(10000);
        return;
    }
    update_team_list(s, client_fd, name, description);
    server_event_team_created(s->uuid_team, name, uuid_str);
}
