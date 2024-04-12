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
        new_user->log = false;
        new_user->name = name;
        new_user->next = NULL;
    }
    return new_user;
}

void add_user(user_t **head, char *name)
{
    user_t *new_user = create_user(name);
    user_t *current;

    if (new_user == NULL) {
        printf("Error in user creation\n");
        return;
    }
    if (*head == NULL) {
        *head = new_user;
    } else {
        current = *head;
        if (current->next == NULL) {
            current->next = new_user;
            return;
        }
        for (int i = 0; current->next != NULL; i++) {
            current = current->next;
        }
        current->next = new_user;
    }
}

int search_name(user_t *current, char *name)
{
    int indice = 0;

    if (current->next == NULL) {
        if (strcmp(current->name, name) == 0) {
            return indice;
        }
    }
    while (current->next != NULL) {
        if (strcmp(current->name, name) == 0) {
            return indice;
        }
        indice++;
        current = current->next;
    }
    if (strcmp(current->name, name) == 0) {
        return indice;
    }
    // printf("User not found\n");
    return -1;
}

int find_user(user_t **head, char *name)
{
    user_t *current;

    if (*head == NULL) {
        //printf("User not found\n");
        return -1;
    } else {
        current = *head;
        return search_name(current, name);
    }
    return -1;
}
