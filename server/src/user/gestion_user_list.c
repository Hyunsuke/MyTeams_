/*
** EPITECH PROJECT, 2024
** gestion_user_list.c
** File description:
** function for user list
*/

#include "server.h"

user_t *create_user(server_t *s, char *name)
{
    user_t *new_user = my_malloc(sizeof(user_t));
    char uuid_str[37] = "";

    if (new_user != NULL) {
        if (s->save_struct->is_uuid_there && !s->save_struct->is_saving) {
            uuid_parse(s->save_struct->uuid, new_user->uuid);
            strcpy(s->save_struct->uuid, uuid_str);
        } else {
            uuid_generate(new_user->uuid);
            uuid_unparse(new_user->uuid, uuid_str);
        }
        new_user->log = 1;

        new_user->context = my_strdup(uuid_str);
        new_user->name = my_strdup(name);
        new_user->next = NULL;
    }
    return new_user;
}

void add_user(server_t *s, user_t **head, char *name)
{
    user_t *new_user = create_user(s, name);
    user_t *current = *head;

    if (new_user == NULL) {
        printf("Error in user creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_user;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_user;
    }
}

user_t *find_user_by_uuid(user_t *head, const char *uuid)
{
    user_t *current = head;
    char uuid_str[37];

    while (current != NULL) {
        uuid_unparse(current->uuid, uuid_str);
        if (strcmp(uuid_str, uuid) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

user_t *find_user_by_name(user_t *head, const char *name)
{
    user_t *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

user_t *find_user_by_fd(client_t *head_client,
    user_t *head_user, int client_fd)
{
    client_t *current_client = head_client;

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            return find_user_by_name(head_user, current_client->name);
        }
        current_client = current_client->next;
    }
    return NULL;
}
