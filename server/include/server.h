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
    int log;
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
    char *name_logout;
    bool is_Ctrl_c;
} server_t;

void printhelp(void);
int error_handling(int ac, char **av);
void run_serv(server_t *s);
void config(server_t *s);

//gestion_client_list.c
void add_client(client_t **head, int fd);
void remove_client(client_t **head, int fd, server_t *s);
client_t *find_client_by_name(client_t *head, const char *name);

//modif_login.c
int update_client_name(client_t **head, int fd, char *name);
void display_clients(server_t *s);

//gestion_user_list.c
void add_user(user_t **head, char *name);
user_t *find_user_by_uuid(user_t *head, const char *uuid);
user_t *find_user_by_name(user_t *head, const char *name);
user_t *find_user_by_fd(client_t *head_client,
    user_t *head_user, int client_fd);

//modif_login.c
void update_user(user_t **head, client_t **head_client, int fd, char *name);

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
int check_connection_client(client_t *current_client, int client_fd);

//handle_commands.c
void handle_commands(server_t *s, int client_fd);

//cmd_login.c
void login_cmd(server_t *s, int client_fd);

//cmd_logout.c
void logout_cmd(server_t *s, int client_fd);
void update_user_and_client_logout(server_t *s, user_t **user_head,
    client_t **client_head, int cli_fd);
int logout_client(client_t *current_client, int cli_fd, server_t *s);
void logout_user(user_t *current_user, server_t *s, int cli_fd);

//cmd_users.c
void users_cmd(server_t *s, int client_fd);

//cmd_user.c
void user_cmd(server_t *s, int client_fd);

//send_infos.c
void send_uuid_to_client(int client_fd, char *uuid_str);
void send_name_to_client(int client_fd, char *name_str);
void send_status_to_client(int client_fd, char *status);
void send_logged_in_to_client(int client_fd);
void send_message_to_client(int client_fd, char *mess);
void send_send_to_client(int client_fd);
void send_logged_out_to_client(int client_fd);
void send_users_to_client(int client_fd);
void send_unauthorized_to_client(int client_fd);
void send_user_to_client(int client_fd);
void send_unknown_user_to_client(int client_fd);

// cmd_send.c
void send_cmd(server_t *s, int client_fd);
void send_bad_uuid(int client_fd, char *uuid);

// client/modif_send.c
int find_client(server_t *s, int client_fd,
    user_t *dest_user, client_t **dest_client);
void receive_message(int client_fd, char *sender_uuid, char *message);
void send_bad_uuid(int client_fd, char *uuid);

// user/modif_send.c
int find_sender(server_t *s, int client_fd, user_t **sender_user);
int find_user(server_t *s, int client_fd, char *uuid, user_t **dest_user);

// cmd_messages.c
void messages_cmd(server_t *s, int client_fd);

void display_clients(server_t *s);
void display_users(server_t *s);

typedef struct {
    const char *command;
    void (*handler)(server_t *, int);
} command_handler_t;

#endif /* !SERVER_H_ */
