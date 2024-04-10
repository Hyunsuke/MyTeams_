/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** connection.c
*/

#include "server.h"

void handle_new_connection(server_t *s, fd_set *client_fds, int *max_fd)
{
    socklen_t addr_len = sizeof(s->serv_adr);

    s->entry_socket =
    accept(s->socket_fd, (struct sockaddr *)&s->serv_adr, &addr_len);
    if (s->entry_socket == -1) {
        perror("Erreur lors de l'acceptation de la connexion entrante");
        exit(EXIT_FAILURE);
    }
    FD_SET(s->entry_socket, client_fds);
    if (s->entry_socket > *max_fd)
        *max_fd = s->entry_socket;
    write(s->entry_socket,
    get_ftp_response_message(220), strlen(get_ftp_response_message(220)));
}

void client_is_connected(server_t *s, int client_fd)
{
    char buffer[1024];
    int bytes_received;

    bytes_received = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_received <= 0)
            return;
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
                client_is_connected(server, client_fd);
        }
    }
}

void handle_incoming_connection(server_t *s)
{
    int max_fd = s->socket_fd;
    fd_set read_fds;

    FD_ZERO(&s->client_fds);
    FD_SET(s->socket_fd, &s->client_fds);
    while (!s->exitProgram) {
        read_fds = s->client_fds;
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("Erreur lors de l'utilisation de select");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(s->socket_fd, &read_fds)) {
            handle_new_connection(server, &s->client_fds, &max_fd);
        }
        monitor_select_activity(server, &read_fds, max_fd);
    }
    close(s->socket_fd);
}
