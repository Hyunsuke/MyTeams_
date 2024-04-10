/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_client
*/

#include "client.h"

int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("Erreur lors de la création du socket");
        return -1;
    }
    return sockfd;
}

int client_loop(int sockfd)
{
    char *input_str = NULL;
    size_t size = 0;

    if (getline(&input_str, &size, stdin) == -1) {
        return 1;
    }
    input_str[strlen(input_str) - 1] = '\n';
    send(sockfd, input_str, size, 0);
    return 0;
}

int connect_to_server(char *serv_ip, int serv_port)
{
    int sockfd = create_socket();
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serv_port);
    if (inet_pton(AF_INET, serv_ip, &server_addr.sin_addr) <= 0) {
        printf("can't set the server info\n");
        close(sockfd);
        return -1;
    }
    if (connect(sockfd, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1) {
        printf("can't connect to the server\n");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

int create_client(char *serv_ip, int serv_port)
{
    int sockfd = connect_to_server(serv_ip, serv_port);

    if (sockfd == -1) {
        return 84;
    }
    while (1) {
        if (client_loop(sockfd))
            break;
    }
    close(sockfd);
    return 0;
}
