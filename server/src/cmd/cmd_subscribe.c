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

void send_subscribe_to_subscribed(team_t *current_team, server_t *s)
{
    user_t **user_subscribe_head = &current_team->user;
    user_t *user_subscribe = *user_subscribe_head;
    client_t **client_head;
    client_t *current_client;

    while (user_subscribe != NULL) {
        client_head = &s->clients;
        current_client = *client_head;
        while (current_client != NULL) {
            if (current_client->name != NULL) {
                if (strcmp(user_subscribe->name, current_client->name) == 0) {
                    send(current_client->fd, my_strcat("TEAM_UUID ", s->uuid_team), strlen(s->uuid_team) + 11, 0);
                    usleep(10000);
                    send(current_client->fd, my_strcat("USER_UUID ", s->uuid_user), strlen(s->uuid_user) + 11, 0);
                    usleep(10000);
                    send(current_client->fd, "PRINT_SUBSCRIBE_EVENT", 22, 0);
                    usleep(10000);
                }
            }
            current_client = current_client->next;
        }
        user_subscribe = user_subscribe->next;
    }
}

void set_values(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;
    char *name_user;

    while (current_client != NULL) {
        if (client_fd == current_client->fd) {
            name_user = current_client->name;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(name_user, current_user->name) == 0) {
            s->save_name = current_user->name;
            uuid_copy(s->save_uuid, current_user->uuid);
            return;
        }
        current_user = current_user->next;
    }
}

static int user_alrdy_set(char *name, team_t *current_team)
{
    user_t **user_head = &current_team->user;
    user_t *user_subscribe = *user_head;

    while (user_subscribe != NULL) {
        if (strcmp(user_subscribe->name, name) == 0) {
            return 84;
        }
        user_subscribe = user_subscribe->next;
    }
    return 0;
}

user_t *cpy_user(server_t *s, int client_fd, team_t *current_team)
{
    user_t *new_user = my_malloc(sizeof(user_t));

    set_values(s, client_fd);
    if (user_alrdy_set(s->save_name, current_team) == 84) {
        return NULL;
    }
    if (new_user != NULL) {
        new_user->name = s->save_name;
        uuid_copy(new_user->uuid, s->save_uuid);
        new_user->next = NULL;
    }
    return new_user;
}

void add_user_elem(team_t *current_team, server_t *s, int client_fd)
{
    user_t *new_user = cpy_user(s, client_fd, current_team);
    s->uuid_user = get_user_uuid(s, client_fd);
    user_t **user_head = &current_team->user;
    user_t *user_subscribe = *user_head;

    if (new_user == NULL) {
        write(client_fd, "User already in list\n", 22);
        return;
    }
    if (user_subscribe == NULL) {
        *user_head = new_user;
    } else {
        while (user_subscribe->next != NULL) {
            user_subscribe = user_subscribe->next;
        }
        user_subscribe->next = new_user;
    }
    server_event_user_subscribed(s->uuid_team, s->uuid_user);
}

void set_subscribe_user(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, s->uuid_team);
        if (strcmp(s->uuid_team, s->id_team) == 0) {
            add_user_elem(current_team, s, client_fd);
            send_subscribe_to_subscribed(current_team, s);
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
    return 84;
}

void subscribe_cmd(server_t *s, int client_fd)
{
    char *error = "UNKNOWN_TEAM ";
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    if (error_sub(s) == 84)
        return;
    s->id_team = remove_quotes(s->input_tab[1]);
    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return;
    }
    if (team_dont_exist(s) == 84) {
        error = my_strcat(error, s->id_team);
        send(client_fd, error, strlen(error), 0);
        usleep(1000);
        return;
    }
    set_subscribe_user(s, client_fd);
}
