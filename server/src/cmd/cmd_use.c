/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** cmd_use.c
*/

#include "server.h"

client_t *get_client(client_t **client_head, int client_fd)
{
    client_t *current = *client_head;

    while (current != NULL) {
        if (current->fd == client_fd) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static int get_args_number(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

char *set_context(int args, user_t *current, char **array)
{
    char *str = NULL;
    char uuid[37];

    uuid_unparse(current->uuid, uuid);
    str = my_strdup(uuid);
    for (int i = 1; i < args; i++) {
        str = my_strcat(str, "/");
        str = my_strcat(str, array[i]);
    }
    return str;
}

int check_use_error(client_t *current, int client_fd, int args, server_t *s)
{
    if (current == NULL) {
        write(client_fd, "No existing client with the given client_fd\n", 44);
        return 84;
    }
    if (check_connection_client(current, client_fd) == 84) {
        return 84;
    }
    args = get_args_number(s->input_tab);
    if (args < 1 || args > 4) {
        dprintf(client_fd, "403 bad arguments for /use command\n");
        usleep(100);
        return 84;
    }
    return args;
}

int use_cmd(server_t *s, int client_fd)
{
    client_t *current_client = get_client(&s->clients, client_fd);
    user_t *current_user;
    int args = 0;

    args = check_use_error(current_client, client_fd, args, s);
    if (args == 84)
        return 84;
    for (int i = 1; s->input_tab[i] != NULL; i++) {
        if (!check_quotes(s->input_tab[i])) {
            write(client_fd, "user_uuid doesn't start or end with quotes\n",
                strlen("user_uuid doesn't start or end with quotes\n"));
            return 84;
        }
        s->input_tab[i] = remove_quotes(s->input_tab[i]);
    }
    current_user = find_user_by_name(s->users, current_client->name);
    current_user->context = set_context(args, current_user, s->input_tab);
    dprintf(client_fd, "404 context set successfully\n");
    return 0;
}
