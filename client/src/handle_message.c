/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** handle_message.c
*/

#include "client.h"

char *read_stdin(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        printf("Erreur lors de la lecture de l'entrée standard");
        free(buffer);
        return NULL;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

int send_message(int sockfd, const char *message)
{
    ssize_t bytes_sent = send(sockfd, message, strlen(message), 0);

    if (bytes_sent == -1) {
        printf("Erreur lors de l'envoi du message");
        return -1;
    }
    return 0;
}

int receive_message(client_t *c, int sockfd)
{
    char buffer[1024];
    ssize_t bytes_received;
    char **input_commands = NULL;

    bytes_received = recv(sockfd, buffer, 1024, 0);
    if (bytes_received == -1) {
        printf("Erreur lors de la réception des données du serveur");
        return -1;
    } else if (bytes_received == 0) {
        printf("550 server closed the connection\n");
        return 1;
    } else {
        buffer[bytes_received] = '\0';
    }
    input_commands = my_str_to_word_array(buffer, ' ');
    handle_commands(c, input_commands, buffer);
    return 0;
}

int handle_stdin_input(int sockfd)
{
    char *input = read_stdin();

    if (input == NULL) {
        return 1;
    }
    if (send_message(sockfd, input) == -1) {
        free(input);
        return 1;
    }
    free(input);
    return 0;
}

int handle_server_data(client_t *c, int sockfd)
{
    if (receive_message(c, sockfd) != 0) {
        return 1;
    }
    return 0;
}
