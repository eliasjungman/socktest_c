#include <socket.h>

#include <netinet/in.h> //sockets
#include <string.h> //stdlen
#include <unistd.h> // read?
#include <stdio.h>
#include <strings.h>

// https://www.ibm.com/docs/en/i/7.2?topic=sscaaiic-example-accepting-connections-from-both-ipv6-ipv4-clients
int create_socket() {
    // https://man7.org/linux/man-pages/man2/socket.2.html
    // int socket(int domain, int type, int protocol);
    // cat /etc/protocols
    // ip = 0
    // tcp = 6
    // udp = 17
    // vain ip protokolla toimii
    int socket1 = socket(AF_INET, SOCK_STREAM, 0);
    return socket1;
}

void free_socket(int client_socket) {
    // pakota portti vapaaksi
    int opt = 1;
    setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
}

void turn_timeout(int sockfd) {
    //https://linux.die.net/man/2/setsockopt
    // "copy paste" code
    // https://github.com/moret/socket-read-timeout/blob/master/client.c
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

}

char *read_data(int client_socket) {
    char *data = "";
    while(1) {
        char buffer[BUFFER_SIZE] = "";
        int reader = read(client_socket, buffer, BUFFER_SIZE);
        if (reader == 0) {
            printf("read_data: closed\n");
            return NULL;
        } else if (reader != BUFFER_SIZE) {
            //printf("data: %s\n", buffer);
            printf("read_data: reader != BUFFER_SIZE\n");
            return NULL;
        } else {
            //printf("data: %s\n", buffer);
            //fflush(stdout);
            //data += buffer;
            data = concat(data, buffer);
            if (strcmp(buffer, ESCAPE_CHAR) == 0) {
                return data;
            }
        }
    }
}

void send_data(int client_socket, char *string) {
    if (send(client_socket, string, strlen(string), 0) != strlen(string)) {
        printf("send_data: error happened while sending data\n");
    }
}
