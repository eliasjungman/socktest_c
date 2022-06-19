// gcc -I include/ -o server.out udptest_main.c socket.c strings.c server.c udphandler.c

#include <stdio.h>
#include <socket.h>
#include <server.h>
#include <udphandler.h>

#include <netinet/in.h>
#include <unistd.h> //fork, close
#include <signal.h>

#define PORT 8080
int main() {
    int socket1 = socket(AF_INET, SOCK_DGRAM, 0);
    free_socket(socket1);

    bind_socket(socket1, PORT);

    int pid = fork();

    if (pid == 0) {
        uhandler_write(socket1);
    }

    printf("forked. fork pid is: %d\n", pid);
    uhandler_read(socket1);

    kill(pid, SIGKILL);
    close(socket1);

    return 0;
}
