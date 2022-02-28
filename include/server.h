#ifndef SERVER_H
#define SERVER_H

#define SIN_FAMILY AF_INET
#define SIN_ADDR INADDR_ANY

void bind_socket(int client_socket, int port);

#endif