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

typedef struct user {
    bool log;
    char *name;
    struct user *next;
} user_t;

typedef struct client {
    uuid_t uuid;
    int fd;
    char *name;
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
void add_client(client_t **head, int fd);
int find_client(client_t **head, int fd);

//gestion_user_list.c
void add_user(user_t **head, char *name);
int find_user(user_t **head, char *name);

// list.c
void init_list(server_t *s);
void init_server(server_t *s);

// connection.c
void handle_incoming_connection(server_t *s);
void monitor_select_activity(server_t *s, fd_set *client_fds, int max_fd);
int handle_new_connection(server_t *s, fd_set *client_fds, int *max_fd);

// utils.c
char **my_str_to_word_array(char const *str, char separator);
int number_back(char const *str, char separator);
bool check_quotes(const char *str);
char *remove_quotes(const char *str);

//handle_commands.c
void handle_commands(server_t *s, int client_fd);

//cmd_login.c
void login_cmd(server_t *s, int client_fd);

typedef struct {
    const char *command;
    void (*handler)(server_t *, int);
} command_handler_t;

#endif /* !SERVER_H_ */
