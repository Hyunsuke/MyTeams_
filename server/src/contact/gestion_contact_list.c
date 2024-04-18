/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** gestion_contact_list.c
*/

#include "server.h"

contact_t *create_contact(char *uuid)
{
    contact_t *new_contact = my_malloc(sizeof(contact_t));

    if (new_contact != NULL) {
        new_contact->uuid = my_strdup(uuid);
        new_contact->content = NULL;
        new_contact->next = NULL;
    }
    return new_contact;
}

void add_contact(contact_t **head, char *uuid)
{
    contact_t *new_contact = create_contact(uuid);
    contact_t *current = *head;

    if (new_contact == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_contact;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_contact;
    }
}

contact_t *find_contact_by_uuid(contact_t *head, char *uuid)
{
    contact_t *current = head;

    if (current == NULL) {
        return current;
    }
    while (current != NULL) {
        if (strcmp(current->uuid, uuid) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

message_t *create_message(char *uuid, char *message, time_t timestamp)
{
    message_t *new_message = my_malloc(sizeof(message_t));

    if (new_message != NULL) {
        new_message->sender_uuid = my_strdup(uuid);
        new_message->timestamp = timestamp;
        new_message->body = message;
        new_message->next = NULL;
    }
    return new_message;
}

void add_message(message_t **head, char *uuid, char *message, time_t timestamp)
{
    message_t *new_message = create_message(uuid, message, timestamp);
    message_t *current = *head;

    if (new_message == NULL) {
        printf("Error in client creation\n");
        return;
    }
    if (current == NULL) {
        *head = new_message;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_message;
    }
}
