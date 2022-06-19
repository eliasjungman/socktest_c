#include <server.h>

#include <netinet/in.h> //sockets
#include <stdio.h>

void bind_socket(int client_socket, int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int addrlen = sizeof(address);

    int status = bind(client_socket, (struct sockaddr *) &address, addrlen);

    if (status < 0) {
        printf("bind failed\n");
    }
}
