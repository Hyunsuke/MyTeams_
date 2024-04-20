/*
** EPITECH PROJECT, 2024
** cmd_create.c
** File description:
** commande /create
*/

#include "server.h"

char **define_context(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    user_t **user_head = &s->users;
    client_t *current_client = *client_head;
    user_t *current_user = *user_head;
    char **context_tab;
    char *save_name;
    char uuid[37];

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            save_name = current_client->name;
            break;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(current_user->name, save_name) == 0) {
            uuid_unparse(current_user->uuid, uuid);
            context_tab = my_str_to_word_array(current_user->context, '/');
            return context_tab;
        }
        current_user = current_user->next;
    }
    return NULL;
}

char *get_type_of_create(server_t *s, int client_fd)
{
    char *type_create;
    int pos = 0;
    char **context_parse = define_context(s, client_fd);

    for (; context_parse[pos] != NULL; pos++);
    if (pos == 1) {
        type_create = "team";
    }
    if (pos == 2) {
        type_create = "channel";
    }
    if (pos == 3) {
        type_create = "thread";
    }
    if (pos == 4) {
        type_create = "reply";
    }
    return type_create;
}

static int check_args_quotes_for_ttc(server_t *s, char *type, int client_fd,
    int nb_args)
{
    if (strcmp(type, "team") == 0 || strcmp(type, "channel") == 0 ||
        strcmp(type, "thread") == 0) {
        if (nb_args != 3) {
            write(client_fd, "Invalid number of args.\n", 24);
            return 84;
        }
        if (check_quotes(s->input_tab[1]) == false ||
            check_quotes(s->input_tab[2]) == false) {
            write(client_fd, "Bad Synthax of arguments.\n", 27);
            return 84;
        }
    }
    return 0;
}

int error_create(server_t *s, char *type, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (check_args_quotes_for_ttc(s, type, client_fd, nb_args) == 84)
        return 0;
    if (strcmp(type, "reply") == 0) {
        if (nb_args != 2) {
            write(client_fd, "Invalid number of args.\n", 24);
            return 84;
        }
        if (check_quotes(s->input_tab[1]) == false) {
            write(client_fd, "Bad Synthax of arguments.\n", 27);
            return 84;
        }
    }
    return 0;
}

void create_element(server_t *s, int client_fd, char *type)
{
    if (strcmp("team", type) == 0) {
        add_team(s, client_fd);
    }
    if (strcmp("channel", type) == 0) {
        add_channel(s, client_fd);
    }
    if (strcmp("thread", type) == 0) {
        add_thread(s, client_fd);
    }
    if (strcmp("reply", type) == 0) {
        add_reply(s, client_fd);
    }
}

int create_cmd(server_t *s, int client_fd)
{
    char *type;
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return 84;
    }
    type = get_type_of_create(s, client_fd);
    if (error_create(s, type, client_fd) == 84) {
        return 84;
    }
    create_element(s, client_fd, type);
    return 0;
}
