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
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <uuid/uuid.h>
    #include <unistd.h>
    #include "stdarg.h"
    #include "../../libs/myteams/logging_client.h"
    #include "../../libs/myteams/logging_server.h"

typedef struct user {
    uuid_t uuid;
    bool log;
    char *name;
    struct user *next;
} user_t;

typedef struct client {
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
    user_t *users;
    char **input_tab;
} server_t;

void printhelp(void);
int error_handling(int ac, char **av);
void run_serv(server_t *s);
void config(server_t *s);

//gestion_client_list.c
void add_client(client_t **head, int fd);
int update_client_name(client_t **head, int fd, char *name);
void display_clients(server_t *s);
void remove_client(client_t **head, int fd, server_t *s);

//gestion_user_list.c
void add_user(user_t **head, char *name);
void update_user(user_t **head, client_t **head_client, int fd, char *name);
void display_users(server_t *s);

// list.c
void init_list(server_t *s);
void init_server(server_t *s);

// connection.c
void handle_incoming_connection(server_t *s);
void monitor_select_activity(server_t *s, fd_set *client_fds, int max_fd);
int handle_new_connection(server_t *s, fd_set *client_fds, int *max_fd);

//my_str_to_word_array.c
char **my_str_to_word_array(char const *str, char separator);
int number_back(char const *str, char separator);

// utils.c
bool check_quotes(const char *str);
char *remove_quotes(const char *str);

//handle_commands.c
void handle_commands(server_t *s, int client_fd);

//cmd_login.c
void login_cmd(server_t *s, int client_fd);

//send_infos.c
void send_uuid_to_client(int client_fd, char *uuid_str);
void send_name_to_client(int client_fd, char *name_str);
void send_logged_in_to_client(int client_fd);

typedef struct {
    const char *command;
    void (*handler)(server_t *, int);
} command_handler_t;

#endif /* !SERVER_H_ */
