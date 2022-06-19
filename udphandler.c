#include <udphandler.h>

#include <socket.h>
#include <stdio.h>
#include <arpa/inet.h> //inet_ntoa -> https://linux.die.net/man/3/inet_ntoa
#include <netinet/in.h>
#include <string.h>

void uhandler_read(int socket1) {
    #define BUFFER 1024

    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    int n;
    while(1) {
        char buffer[BUFFER] = "";
        n = recvfrom(socket1, buffer, BUFFER, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
        printf("socket: %d, ip: %s, port: %d\n", socket1, inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        buffer[n] = '\0';
        printf("user enters: %s\n", buffer);
        fflush(stdout);

    }
}

void uhandler_write(int socket1) {
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;

    #define s_IP "127.0.0.1"
    #define s_PORT 8080
    servaddr.sin_port = htons(s_PORT);
    if(inet_pton(AF_INET, s_IP, &servaddr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return;
    }

    while(1) {
        char *buffer = NULL;
        size_t bufsize;

        getline(&buffer, &bufsize, stdin);
        printf("you typed: %s\n", buffer);
       	sendto(socket1, (const char *)buffer, strlen(buffer),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
    }
}