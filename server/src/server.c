/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server gestion
*/

#include "server.h"

int get_info_from_file(server_t *s, char *temp_buffer, int client_fd)
{
    char **uuid_array = NULL;
    int args = 0;

    if (temp_buffer == NULL)
        return 0;
    uuid_array = my_str_to_word_array(temp_buffer, '\e');
    while (uuid_array[args] != NULL)
        args++;
    if (args == 1)
        s->save_struct->buffer = temp_buffer;
    else {
        if (uuid_array[1] == NULL)
            return 84;
        if (uuid_array[1][0] == '\0')
            return 84;
        s->save_struct->is_uuid_there = true;
        s->save_struct->uuid = my_strdup(uuid_array[1]);
    }
    s->input_tab = my_str_to_word_array(uuid_array[0], ' ');
    return handle_commands(s, client_fd);
}

static int get_fd_from_array(server_t *s, char *buffer, int client_fd)
{
    char **array = NULL;
    int args = 0;
    client_t *current;

    if (buffer == NULL)
        return 0;
    array = my_str_to_word_array(buffer, '#');
    for (; array[args] != NULL; args++);
    if (args == 2) {
        if (array[1] == NULL)
            return 84;
        if (array[1][0] == '\0')
            return 84;
        current = find_client_by_name(s->clients, array[1]);
        if (current == NULL)
            return 84;
        s->save_struct->buffer = buffer;
        return get_info_from_file(s, array[0], current->fd );
    }
    return get_info_from_file(s, array[0], client_fd);
}

static void set_logout(server_t *s)
{
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;

    while (current_user != NULL) {
        current_user->log -= 1;
        current_user = current_user->next;
    }
}

static int commands_load(server_t *s, char **array, int nb_login)
{
    int *int_array = my_malloc(sizeof(int) * nb_login + 1);
    int add = 0;

    for (int i = 0; i < nb_login; i++) {
        int_array[i] = i + 4;
        add_client(&(s->clients), int_array[i]);
    }
    for (int index = 0; array[index] != NULL; index++) {
        if (array[index] == NULL)
            continue;
        if (get_fd_from_array(s, array[index], int_array[add]) == 84)
            return 84;
        if (!strncmp(array[index], "/login", 6))
            add++;
    }
    for (int i = 0; i < nb_login; i++) {
        remove_client(&s->clients, int_array[i], s);
        set_logout(s);
    }
    return 0;
}

static char **get_array_from_file(FILE *file)
{
    size_t buf_size = 0;
    char *str = "";
    char *line = NULL;
    char **array = NULL;

    while (getline(&line, &buf_size, file) != -1) {
        str = my_strcat(str, line);
        line = NULL;
    }
    array = my_str_to_word_array(str, '\n');
    return array;
}

static void get_nb_login(char **array, int *nb_login)
{
    for (int i = 0; array[i] != NULL; i++) {
        if (!strncmp(array[i], "/login", 6))
            (*nb_login)++;
    }
}

int load_file(server_t *s)
{
    FILE *file = fopen("save.txt", "r");
    int nb_login = 0;
    char **array = NULL;

    if (file == NULL)
        return 0;
    array = get_array_from_file(file);
    get_nb_login(array, &nb_login);
    if (commands_load(s, array, nb_login) == 84)
        return 84;
    fclose(file);
    return 0;
}

void run_serv(server_t *s)
{
    init_list(s);
    config(s);
    s->save_struct->buffer = NULL;
    // if (load_file(s) == 84) {
    //     my_free_all();
    //     exit(84);
    // }
    s->save_struct->is_saving = true;
    handle_incoming_connection(s);
}
