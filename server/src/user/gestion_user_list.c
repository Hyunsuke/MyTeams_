/*
** EPITECH PROJECT, 2024
** gestion_user_list.c
** File description:
** function for user list
*/

#include "server.h"

void display_users(server_t *s)
{
    user_t *current_user = s->users;
    int user_num = 1;
    char *log;

    printf("Liste Users:\n");
    if (current_user == NULL)
        printf("Liste User vide\n");
    while (current_user != NULL) {
        if (current_user->log == false) {
            log = "false";
        } else {
            log = "true";
        }
        printf("User %d: name[%s] log[%s]\n", user_num,
            current_user->name, log);
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
        *head = new_user;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_user;
    }
}
