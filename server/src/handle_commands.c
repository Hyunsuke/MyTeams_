/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "server.h"

command_handler_t commandHandlers[] = {
    {"/login", login_cmd},
    {"/logout", logout_cmd},
    {"/users", users_cmd},
    {"/send", send_cmd},
    {"/messages", messages_cmd},
    {"/user", user_cmd},
    {"/help", help_cmd},
    {"/create", create_cmd},
    {"/use", use_cmd},
    {"/subscribe", subscribe_cmd},
    {"/list", list_cmd},
    {"/info", info_cmd},
    {NULL, NULL}
};

int process_command(server_t *s, int client_fd, const char *command)
{
    for (int i = 0; commandHandlers[i].command != NULL; ++i) {
        if (strcmp(command, commandHandlers[i].command) == 0) {
            return commandHandlers[i].handler(s, client_fd);
        }
    }
    return 0;
}

void push_back_save(server_t *s, char *buffer, int client_fd)
{
    FILE *file = fopen("save.txt", "a");
    user_t *current;

    if (buffer == NULL)
        return;
    current = find_user_by_fd(s->clients, s->users, client_fd);
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier save.txt\n");
        return;
    }
    if (s->isClientUpdated == false) {
        buffer = my_strcat(buffer, "#");
        buffer = my_strcat(buffer, current->name);
    }
    if (buffer == NULL)
        return;
    fprintf(file, "%s\n", buffer);
    fclose(file);
}

int handle_commands(server_t *s, int client_fd)
{
    int save_return = 0;

    s->isClientUpdated = false;
    save_return = process_command(s, client_fd, s->input_tab[0]);
    if (s->save_struct->is_saving) {
        if (save_return == 0) {
            push_back_save(s, s->save_struct->buffer, client_fd);
            return save_return;
        }
    }
    return save_return;
}
