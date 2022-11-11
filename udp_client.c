#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

// UDP client-side implementation
int main()
{
    int sockfd;
    char *message = "hello there, server!";
    char buffer[1024];

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(PORT);
    client_address.sin_addr.s_addr = inet_addr("192.168.1.7");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.13");

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("Socket opening error");
        return -1;
    }

    if ((bind(sockfd, (struct sockaddr *)&client_address, sizeof(client_address))) < 0)
    {
        printf("Bind error");
        return -1;
    }

    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_address, sizeof(server_address));

    int addrlen = sizeof(struct sockaddr_in);
    if (recvfrom(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &addrlen) == -1)
    {
        perror("Received message error");
        return -1;
    }
    printf("Server message: %s", buffer);
    close(sockfd);
    return 0;
}