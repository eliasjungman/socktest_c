// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <client.h>

//gcc -I include/ -o client.out test.c client.c
	
#define IP "127.0.0.1"
#define PORT	 8080
#define MAXLINE 1024
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *msg = "GET / HTTP/1.1\r\n";
    struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if(inet_pton(SIN_FAMILY, IP, &servaddr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return 1;
    }
		
	int n, len;
		
	sendto(sockfd, (const char *)msg, strlen(msg),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("%s message sent.\n", msg);

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
	
	close(sockfd);
	return 0;
}
