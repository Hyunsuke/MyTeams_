/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** connection.c
*/

#include "server.h"

int handle_new_connection(server_t *s, fd_set *client_fds, int *max_fd)
{
    socklen_t addr_len = sizeof(s->serv_adr);
    int new_client = 0;

    new_client =
    accept(s->server_fd, (struct sockaddr *)&s->serv_adr, &addr_len);
    if (new_client == -1) {
        printf("Erreur lors de l'acceptation de la connexion entrante\n");
        return 84;
    }
    FD_SET(new_client, client_fds);
    if (new_client > *max_fd)
        *max_fd = new_client;
    add_client(&(s->clients), new_client);
    return 0;
}

void client_is_connected(server_t *s, int client_fd)
{
    char buffer[1024];
    int bytes_received = 0;

    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
            return;
    if (bytes_received == 0) {
        s->is_Ctrl_c = true;
        update_user_and_client_logout(s, &s->users, &s->clients, client_fd);
        remove_client(&s->clients, client_fd, s);
        return;
    }
    buffer[bytes_received] = '\0';
    s->input_tab = my_str_to_word_array(buffer, ' ');
    handle_commands(s, client_fd);
}

void monitor_select_activity(server_t *s, fd_set *client_fds, int max_fd)
{
    fd_set read_fds;
    int client_fd;

    read_fds = *client_fds;
    for (client_fd = 0; client_fd <= max_fd; client_fd++) {
        if (FD_ISSET(client_fd, &read_fds)) {
            client_is_connected(s, client_fd);
        }
    }
}

void handle_incoming_connection(server_t *s)
{
    int max_fd = s->server_fd;
    fd_set read_fds;

    FD_ZERO(&s->client_fds);
    FD_SET(s->server_fd, &s->client_fds);
    while (!s->exitProgram) {
        read_fds = s->client_fds;
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            printf("Erreur lors de l'utilisation de select");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(s->server_fd, &read_fds)) {
            handle_new_connection(s, &s->client_fds, &max_fd);
        }
        monitor_select_activity(s, &read_fds, max_fd);
    }
    close(s->server_fd);
}
