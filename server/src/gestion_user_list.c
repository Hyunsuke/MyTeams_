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

    printf("Liste user:\n");
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
        *head = new_user;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_user;
    }
}

void update_cli(user_t **head, client_t **head_client, int cli_fd, char *name)
{
    user_t *new_current;
    char uuid_str[37];

    if (update_client_name(head_client, cli_fd, name) != 84) {
        add_user(head, name);
        new_current = *head;
        uuid_unparse(new_current->uuid, uuid_str);
        // Send la ligne juste en dessous
        send_uuid_to_client(cli_fd, uuid_str);
        usleep(1000);
        send_name_to_client(cli_fd, new_current->name);
        usleep(1000);
        send_logged_in_to_client(cli_fd);
        //
        server_event_user_created(uuid_str, new_current->name);
        server_event_user_logged_in(uuid_str);
    }
}

void update_user(user_t **head, client_t **head_client, int cli_fd, char *name)
{
    user_t *current = *head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->log) {
                dprintf(cli_fd, "User already assigned to a client\n");
            } else {
                if (update_client_name(head_client, cli_fd, name) != 84)
                    current->log = true;
            }
            return;
        }
        current = current->next;
    }
    update_cli(head, head_client, cli_fd, name);
}
