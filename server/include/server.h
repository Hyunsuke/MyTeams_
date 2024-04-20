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
    #include <time.h>
    #include "stdarg.h"
    #include "signal.h"
    #include "../../libs/myteams/logging_client.h"
    #include "../../libs/myteams/logging_server.h"
    #include "garbage_collector.h"

typedef struct message {
    char *sender_uuid; // Qui a envoyé le message? Moi ou César
    time_t timestamp; // Time stamp
    char *body; // Le contenu du message
    struct message *next;
} message_t;

typedef struct contact {
    char *uuid; // Je chercher le uuid de César
    struct message *content;
    struct contact *next;
} contact_t;

typedef struct reply {
    time_t time;
    char *body;
    struct reply *next;
} reply_t;

typedef struct thread {
    uuid_t uuid;
    time_t time;
    char *title;
    char *body;
    reply_t *reply;
    struct thread *next;
} thread_t;

typedef struct channel {
    uuid_t uuid;
    char *name;
    char *description;
    thread_t *thread;
    struct channel *next;
} channel_t;

typedef struct user {
    uuid_t uuid;
    int log;
    char *name;
    char *context;
    contact_t *contact;
    struct user *next;
} user_t;

typedef struct team {
    uuid_t uuid;
    char *name;
    char *description;
    user_t *user;
    channel_t *channel;
    struct team *next;
} team_t;

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
    team_t *team;
    char **input_tab;
    char *name_logout;
    char *name_login;
    char *id_team;
    char *thread_title;
    char *thread_body;
    char *reply_body;
    char *uuid_user;
    char uuid_team[37];
    char uuid_channel[37];
    char uuid_thread[37];
    char **parse_context;
    bool is_Ctrl_c;
    int nb_args_use;
    int cli_fd;
    char *channel_name;
    char *channel_description;
    char *save_name;
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
//modif_login.c
void update_user_not_exiting(server_t *s);
int update_user_existing(server_t *s);
//modif_login.c
int update_client(server_t *s, int client_fd);

//gestion_user_list.c
void add_user(user_t **head, char *name);
user_t *find_user_by_uuid(user_t *head, const char *uuid);
user_t *find_user_by_name(user_t *head, const char *name);
user_t *find_user_by_fd(client_t *head_client,
    user_t *head_user, int client_fd);

//modif_login.c
void update_user_not_exiting(server_t *s);
int update_user_existing(server_t *s);

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
char *my_strdup(const char *src);

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

//cmd_create.c
void create_cmd(server_t *s, int client_fd);
char **define_context(server_t *s, int client_fd);

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
void send_message_list_to_client(int client_fd);
void send_timestamp_to_client(int client_fd, time_t timestamp);

// cmd_send.c
void send_cmd(server_t *s, int client_fd);
void send_bad_uuid(int client_fd, char *uuid);

// client/modif_send.c
int find_client(server_t *s, int client_fd,
    user_t *dest_user, client_t **dest_client);
void receive_message(int client_fd, char *sender_uuid, char *message);
void send_bad_uuid(int client_fd, char *uuid);
// void add_message(user_t *user, time_t timestamp, char *body);

// user/modif_send.c
int find_sender(server_t *s, int client_fd, user_t **sender_user);
int find_user(server_t *s, int client_fd, char *uuid, user_t **dest_user);

// cmd_messages.c
void messages_cmd(server_t *s, int client_fd);

void display_clients(server_t *s);
void display_users(server_t *s);

//cmd_help.c
void help_cmd(server_t *s, int client_fd);

//gestion_contact_list.c
void add_message(message_t **head, char *uuid, char *msg, time_t timestamp);
message_t *create_message(char *uuid, char *message, time_t timestamp);
contact_t *find_contact_by_uuid(contact_t *head, char *uuid);
void add_contact(contact_t **head, char *uuid);
contact_t *create_contact(char *uuid);

//cmd_use.c
void use_cmd(server_t *s, int client_fd);

//my_strcat.c
char *my_strcat(const char *str1, const char *str2);

//gestion_team.c
void add_team(server_t *s, int client_fd);
char *get_user_uuid(server_t *s, int client_fd);

//gestion_thread.C
void add_thread(server_t *s, int client_fd);

//getsion_channel.c
void add_channel(server_t *s, int client_fd);

//gestion_reply.c
void add_reply(server_t *s, int client_fd);

//cmd_subscribe.c
void subscribe_cmd(server_t *s, int client_fd);

//time_conversion_function
char *time_t_to_string(time_t timestamp);

int check_subscribe(team_t *current_team, server_t *s, int client_fd);

typedef struct {
    const char *command;
    void (*handler)(server_t *, int);
} command_handler_t;

#endif /* !SERVER_H_ */
