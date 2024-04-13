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


void printhelp(void);
int error_handling(int ac, char **av);
int create_client(char *serv_ip, int serv_port);

//handle_message.c
int handle_server_data(int sockfd);
int handle_stdin_input(int sockfd);
int receive_message(int sockfd);
int send_message(int sockfd, const char *message);
char *read_stdin(void);

#endif /* !CLIENT_H_ */
