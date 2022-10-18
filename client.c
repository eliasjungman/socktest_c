#include <client.h>

#include <netinet/in.h> //sockets
#include <arpa/inet.h> //inet_pton -> https://linux.die.net/man/3/inet_ntoa
#include <stdio.h>

int conn_socket(int client_socket, char *ip, int port) {
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if(inet_pton(server.sin_family, ip, &server.sin_addr) <= 0) {
        printf("Invalid address\n");
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("connection failed\n");
        return 1;
    }

    return 0;
}
