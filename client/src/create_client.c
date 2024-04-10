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

int create_client(char *serv_ip, int serv_port)
{
    int sockfd = create_socket();
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serv_port);
    if (inet_pton(AF_INET, serv_ip, &server_addr.sin_addr) <= 0) {
        printf("can't set the server info\n");
        close(sockfd);
        return 84;
    }
    if (connect(sockfd, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1) {
        printf("can't connect to the server\n");
        close(sockfd);
        return 84;
    }
    close(sockfd);
    return 0;
}
