#include <handler.h>

#include <socket.h>
#include <stdio.h>

void handler_read(int client_socket) {
    while(1) {
        char *data = read_data(client_socket);

        if (data == NULL) {
            break;
        }

        printf("user enters: %s\n", data);
        fflush(stdout);
    }
}

void handler_write(int client_socket) {
    while(1) {
        char *buffer = NULL;
        size_t bufsize;

        getline(&buffer, &bufsize, stdin);
        printf("you typed: %s\n", buffer); // debugging printf (trash?)

        send_data(client_socket, buffer);
    }
}
