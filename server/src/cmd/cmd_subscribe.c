/*
** EPITECH PROJECT, 2024
** cmd_subscribe.c
** File description:
** commande subscribe
*/

#include "server.h"

int error_sub(server_t *s)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (nb_args != 2) {
        write(1, "Too many arguments for /sub command\n",
            strlen("Too many arguments for /sub command\n"));
        return 84;
    }
    if (check_quotes(s->input_tab[1]) == false) {
        write(1, "Name doesn't start or end with quotes\n",
            strlen("Name doesn't start or end with quotes\n"));
        return 84;
    }
    return 0;
}

user_t *get_actual_user(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;
    user_t *new_user;
    char *save_name;

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            save_name = current_client->name;
            break;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(current_user->name, save_name) == 0) {
            new_user = current_user;
            return new_user;
        }
        current_user = current_user->next;
    }
    return NULL;
}

void add_user_elem(team_t *current_team, server_t *s, int client_fd)
{
    user_t *new_user = get_actual_user(s, client_fd);
    char *uuid_user = get_user_uuid(s, client_fd);
    user_t **user_head = &current_team->user;
    user_t *user_subscribe = *user_head;

    if (user_subscribe == NULL) {
        *user_head = new_user;
    } else {
        while (user_subscribe->next != NULL) {
            user_subscribe = user_subscribe->next;
        }
        user_subscribe->next = new_user;
    }
    server_event_user_subscribed(s->uuid_team, uuid_user);
}

void set_subscribe_user(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, s->uuid_team);
        if (strcmp(s->uuid_team, s->id_team) == 0) {
            add_user_elem(current_team, s, client_fd);
        }
        current_team = current_team->next;
    }
}

int team_dont_exist(server_t *s)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    char uuid[37];

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, uuid);
        if (strcmp(uuid, s->id_team) == 0) {
            return 0;
        }
        current_team = current_team->next;
    }
    return 84;
}

int check_subscribe(team_t *current_team, server_t *s, int client_fd)
{
    char *uuid = get_user_uuid(s, client_fd);
    user_t **user_head = &current_team->user;
    user_t *current_user = *user_head;
    char uuid_team_user[37];
    
    while (current_user != NULL) {
        uuid_unparse(current_user->uuid, uuid_team_user);
        if (strcmp(uuid, uuid_team_user) == 0) {
            return 0;
        }
        current_user = current_user->next;
    }
    send_unauthorized_to_client(client_fd);
    return 84;
}

void subscribe_cmd(server_t *s, int client_fd)
{
    char *error = "UNKNOWN_TEAM ";

    if (error_sub(s) == 84)
        return;
    s->id_team = remove_quotes(s->input_tab[1]);
    if (team_dont_exist(s) == 84) {
        write(client_fd, "Try to subscribe to an unknown team\n", 37);
        error = my_strcat(error, s->id_team);
        send(client_fd, error, strlen(error), 0);
    }
    set_subscribe_user(s, client_fd);
}
