#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

int main()
{
    int sockfd;
    char *message = "hello there, client!";
    char buffer[1024];

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.13");

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("Socket opening error");
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding error");
        return -1;
    }

    int addrlen = sizeof(client_address);
    if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &addrlen) == -1)
    {
        perror("Received message error");
        return -1;
    }
    printf("Client message: %s\n", buffer);
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&client_address, addrlen);
    close(sockfd);
    
    return 0;
}