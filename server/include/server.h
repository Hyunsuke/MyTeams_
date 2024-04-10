/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "stdbool.h"
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <uuid/uuid.h>

typedef struct client {
    uuid_t uuid;
    int fd;
    char *name;
    bool log;
    struct client *next;
} client_t;

typedef struct server_s {
    int port;
    int server_fd;
    struct sockaddr_in serv_adr;
    bool exitProgram;
    fd_set client_fds;
    client_t *clients;
} server_t;

void printhelp(void);
int error_handling(int ac, char **av);
void run_serv(server_t *s);
void config(server_t *s);
void add_client(client_t **head, int fd);
int find_client(client_t **head, int fd);

// list.c
void init_list(server_t *s);
void init_server(server_t *s);

//connection.c
void handle_incoming_connection(server_t *s);
void monitor_select_activity(server_t *s, fd_set *client_fds, int max_fd);
int handle_new_connection(server_t *s, fd_set *client_fds, int *max_fd);

#endif /* !SERVER_H_ */
