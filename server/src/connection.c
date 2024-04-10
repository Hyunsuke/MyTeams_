/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** connection.c
*/

#include "server.h"

void handle_new_connection(server_t *server, fd_set *client_fds, int *max_fd)
{
    socklen_t addr_len = sizeof(server->_address);

    server->entry_socket =
    accept(server->socket_fd, (struct sockaddr *)&server->_address, &addr_len);
    if (server->entry_socket == -1) {
        perror("Erreur lors de l'acceptation de la connexion entrante");
        exit(EXIT_FAILURE);
    }
    FD_SET(server->entry_socket, client_fds);
    if (server->entry_socket > *max_fd)
        *max_fd = server->entry_socket;
    // write(server->entry_socket,
    // get_ftp_response_message(220), strlen(get_ftp_response_message(220)));
}
