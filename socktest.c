#include <stdio.h>
#include <socket.h>
#include <server.h>

#include <netinet/in.h> //function listen, accept -> sockets
#include <string.h> //strcmp
#include <unistd.h> //fork
#include <stdlib.h> //exit
#include <arpa/inet.h> //inet_ntoa -> https://linux.die.net/man/3/inet_ntoa

#define PORT 8080

void handler(int client_socket) {
    while(1) {
        char *data = read_data(client_socket);
        printf("user enters: %s\n", data);
        fflush(stdout);

        if (data == NULL) {
            break;
        } else if (strcmp(data, "close\r\n") == 0) {
            shutdown(client_socket, 2);
        }
    }
}

int main() {
    int socket1 = create_socket();
    free_socket(socket1);

    int port = PORT;
    bind_socket(socket1, port);
    listen(socket1, 5);

    // //conn_socket(socket1, "127.0.0.1", 80);

    // //exit(0);
    while(1) {
        struct sockaddr_in server_address;
        int len = sizeof(server_address);

        printf("waiting\n");
        int client_socket = accept(socket1, (struct sockaddr *) &server_address, (socklen_t *) &len);

        int pid = fork();

        if (pid == 0) {
            printf("socket: %d, ip: %s, port: %d\n", client_socket, inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
            handler(client_socket);

            exit(0);
        }

        printf("forked. fork pid is: %d\n", pid);
    }
	return 0;
}