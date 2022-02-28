// gcc -I include/ -o server.out server_main.c socket.c strings.c server.c handler.c

#include <stdio.h>
#include <socket.h>
#include <server.h>
#include <handler.h>

#include <netinet/in.h> //function listen, accept -> sockets
#include <unistd.h> //fork, close
#include <arpa/inet.h> //inet_ntoa -> https://linux.die.net/man/3/inet_ntoa
#include <signal.h> // kill child

#define PORT 8080
#define LISTEN_COUNT 0

int main() {
    while(1) {
        int socket = create_socket();
        free_socket(socket);

        bind_socket(socket, PORT);
        listen(socket, LISTEN_COUNT);

        struct sockaddr_in server_address;
        int len = sizeof(server_address);

        printf("waiting for connection\n");
        int client_socket = accept(socket, (struct sockaddr *) &server_address, (socklen_t *) &len);

        printf("socket: %d, ip: %s, port: %d\n", client_socket, inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));

        int pid = fork();

        if (pid == 0) {
            handler_write(client_socket);
        }

        printf("forked. fork pid is: %d\n", pid);

        handler_read(client_socket);

        printf("Disconnected\n");
        kill(pid, SIGKILL);
        close(socket);
    }

    return 0;
}
