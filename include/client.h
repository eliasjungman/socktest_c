#ifndef CLIENT_H
#define CLIENT_H

#define SIN_FAMILY AF_INET

int conn_socket(int client_socket, char *ip, int port);

#endif