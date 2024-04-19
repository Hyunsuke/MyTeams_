/*
** EPITECH PROJECT, 2024
** test_myteams
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #define BUFFER_SIZE 1024

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <ctype.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include "../../libs/myteams/logging_client.h"
    #include "../../libs/myteams/logging_server.h"

typedef struct client {
    char *name;
    char *uuid_str;
    char *message;
    bool log;
    int status;

    //thread
    char *thread_uuid;
    time_t thread_timestamp;
    char *thread_title;
    char *thread_body;

    //user
    char *user_uuid;

    //reply
    char *reply_body;
    time_t reply_timestamp;

    //team
    char *team_uuid;
    char *team_name;
    char *team_description;

    //Channel
    char *channel_uuid;
    char *channel_name;
    char *channel_description;
} client_t;

void printhelp(void);
int error_handling(int ac, char **av);
int create_client(client_t *c, char *serv_ip, int serv_port);

//handle_message.c
int handle_server_data(client_t *c, int sockfd);
int handle_stdin_input(int sockfd);
int receive_message(client_t *c, int sockfd);
int send_message(int sockfd, const char *message);
char *read_stdin(void);

//handle_commands.c
void handle_commands(client_t *c, char **commands, char *buffer);
void process_command(client_t *c, char *first_inp, char **commands, char *buf);

//cmd
void set_uuid(client_t *c, char **commands);
void set_name(client_t *c, char **commands);
void set_message(client_t *c, char **commands);
void set_status(client_t *c, char **commands);
void print_logged_in(client_t *client, char **commands);
void print_send(client_t *client, char **commands);
void print_logged_out(client_t *client, char **commands);
void print_users(client_t *client, char **commands);
void print_unauthorized(client_t *client, char **commands);
void print_unknown_user(client_t *client, char **commands);
void print_user(client_t *client, char **commands);
void print_help(client_t *c, char **commands);
void print_unknown_team(client_t *client, char **commands);
void print_unknown_channel(client_t *client, char **commands);
void print_unknown_thread(client_t *client, char **commands);

// Thread
void set_thread_uuid(client_t *client, char **commands);
void set_thread_timestamp(client_t *client, char **commands);
void set_thread_title(client_t *client, char **commands);
void set_thread_body(client_t *client, char **commands);

// User
void set_user_uuid(client_t *client, char **commands);

// Reply
void set_reply_body(client_t *client, char **commands);
void set_reply_timestamp(client_t *client, char **commands);

// Team
void set_team_uuid(client_t *client, char **commands);
void set_team_name(client_t *client, char **commands);
void set_team_description(client_t *client, char **commands);

// Channel
void set_channel_uuid(client_t *client, char **commands);
void set_channel_name(client_t *client, char **commands);
void set_channel_description(client_t *client, char **commands);

void print_reply_received(client_t *client, char **commands);
void print_reply_created(client_t *client, char **commands);

//my_str_to_word_array.c
char **my_str_to_word_array(char const *str, char separator);

char *strptime(const char *restrict s, const char *restrict format,
    struct tm *restrict tm);

typedef struct {
    const char *command;
    void (*handler)(client_t *, char **);
} command_handler_t;

#endif /* !CLIENT_H_ */
