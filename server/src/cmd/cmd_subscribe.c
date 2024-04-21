/*
** EPITECH PROJECT, 2024
** cmd_subscribe.c
** File description:
** commande subscribe
*/

#include "server.h"

static int error_sub(server_t *s)
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

void send_if_saving(server_t *s, team_t *current_team)
{
    if (s->save_struct->is_saving)
        send_subscribe_to_subscribed(current_team, s);
}

void set_subscribe_user(server_t *s, int client_fd)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, s->uuid_team);
        if (strcmp(s->uuid_team, s->id_team) == 0) {
            add_user_elem(current_team, s, client_fd);
            send_if_saving(s, current_team);
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

static int check_log_exist(server_t *s, int client_fd,
    client_t *current_client)
{
    char *error = "UNKNOWN_TEAM ";

    if (check_connection_client(current_client, client_fd) == 84) {
        if (s->save_struct->is_saving)
            send_unauthorized_to_client(client_fd);
        usleep(1000);
        return 84;
    }
    if (team_dont_exist(s) == 84) {
        error = my_strcat(error, s->id_team);
        if (s->save_struct->is_saving)
            send(client_fd, error, strlen(error), 0);
        usleep(1000);
        return 84;
    }
    return 0;
}

int subscribe_cmd(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    if (error_sub(s) == 84)
        return 84;
    s->id_team = remove_quotes(s->input_tab[1]);
    if (check_log_exist(s, client_fd, current_client) == 84)
        return 84;
    set_subscribe_user(s, client_fd);
    return 0;
}
