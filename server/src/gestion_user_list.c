/*
** EPITECH PROJECT, 2024
** gestion_user_list.c
** File description:
** function for user list
*/

#include "server.h"

void display_users(server_t *s)
{
    printf("Liste user:\n");
    user_t *current_user = s->users;
    int user_num = 1;

    if (current_user == NULL)
        printf("Liste user vide\n");
    while (current_user != NULL) {
        printf("user %d: [%s]\n", user_num, current_user->name);
        current_user = current_user->next;
        user_num++;
    }
}

user_t *create_user(char *name)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (new_user != NULL) {
        uuid_generate(new_user->uuid);
        new_user->log = true;
        new_user->name = strdup(name);
        new_user->next = NULL;
    }
    return new_user;
}

void add_user(user_t **head, char *name)
{
    user_t *new_user = create_user(name);
    user_t *current = *head;

    if (new_user == NULL) {
        printf("Error in user creation\n");
        return;
    }

    if (current == NULL) {
        *head = new_user; // Met à jour le pointeur de tête
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_user;
    }
}

void update_user(user_t **head, client_t **head_client, int client_fd, char *name)
{
    user_t *current = *head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->log) {
                dprintf(client_fd, "User already assigned to a client\n");
            } else {
                if (update_client_name(head_client, client_fd, name) != 84)
                    current->log = true;
            }
            return;
        }
        current = current->next;
    }

    if (update_client_name(head_client, client_fd, name) != 84) {
        add_user(head, name);
        user_t *new_current = *head;
        char uuid_str[37];
        uuid_unparse(new_current->uuid, uuid_str);
        write(client_fd, uuid_str, strlen(uuid_str));
        // client_event_logged_in(uuid_str, current->name);
        // server_event_user_created(uuid_str, current->name);
    }
}
