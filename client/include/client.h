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


void printhelp(void);
int error_handling(int ac, char **av);
int create_client(char *serv_ip, int serv_port);

#endif /* !CLIENT_H_ */
