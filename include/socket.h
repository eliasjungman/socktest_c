#ifndef SOCKET_H
#define SOCKET_H

#define BUFFER_SIZE 1
#define ESCAPE_CHAR "\n"

int create_socket();
void free_socket(int client_socket);
char *read_data(int client_socket);
void send_data(int client_socket, char *string);

#endif