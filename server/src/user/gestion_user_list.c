/*
** EPITECH PROJECT, 2024
** gestion_user_list.c
** File description:
** function for user list
*/

#include "server.h"

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
        *head = new_user;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_user;
    }
}
