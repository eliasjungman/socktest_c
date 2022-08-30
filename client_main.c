// gcc -I include/ -o client.out client_main.c socket.c strings.c client.c

#include <stdio.h>
#include <socket.h>
#include <client.h>
#include <string.h> //strcmp
#include <netinet/in.h> //shutdown
#include <unistd.h> //close

#define IP "127.0.0.1"
#define PORT 8080

void handler(int client_socket) {
    send_data(client_socket, "connected\r\n");

    while(1) {
        char *data = read_data(client_socket);
        printf("%s\n", data);
        fflush(stdout);

        if (data == NULL) {
            break;
        } else if (strcmp(data, "close\n") == 0) {
            shutdown(client_socket, 2);
        }
    }
}

int main() {
    while(1) {
        int socket = create_socket();
        free_socket(socket);

        printf("connecting...\n");
        int status = conn_socket(socket, IP, PORT);
        if (status == 0) {
            printf("connected!\n");
            handler(socket);
            printf("disconnected\n");
        }
        close(socket);
    }

    return 0;
}