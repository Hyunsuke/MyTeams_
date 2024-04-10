/*
** EPITECH PROJECT, 2024
** config.c
** File description:
** configure serv
*/

#include "server.h"

void config_server_socket(server_t *s)
{
    int opt = 1;

    s->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s->server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(s->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
        sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    s->serv_adr.sin_family = AF_INET;
    s->serv_adr.sin_addr.s_addr = INADDR_ANY;
    s->serv_adr.sin_port = htons(atoi(s->port));
}

void config(server_t *s)
{
    config_server_socket(s);
    if (bind(s->server_fd, (struct sockaddr*)&s->serv_adr,
        sizeof(s->serv_adr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(s->server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}
