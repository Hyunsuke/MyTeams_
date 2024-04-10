/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_client
*/

#include "client.h"

#define BUFFER_SIZE 1024

int create_client(char *serv_ip, int serv_port)
{
    char ip_address[INET_ADDRSTRLEN];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("can't create the socket\n");
        return 84;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serv_port);
    if (inet_pton(AF_INET, serv_ip, &server_addr.sin_addr) <= 0) {
        printf("can't set the server info\n");
        close(sockfd);
        return 84;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("can't connect to the server\n");
        close(sockfd);
        return 84;
    }

    char buffer[BUFFER_SIZE];
    ssize_t num_bytes = read(sockfd, buffer, BUFFER_SIZE - 1);
    if (num_bytes == -1) {
        printf("can't read the server message");
        close(sockfd);
        return 84;
    }

    buffer[num_bytes] = '\0';
    printf("Server said: %s\n", buffer);

    close(sockfd);

    return 0;
}
