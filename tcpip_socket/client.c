#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 3333
#define M_MAX_BUFF_SIZE  256


int main(int argc, char*argv[])
{
    int clt_sock_fd;
    struct sockaddr_in srv_addr;
    char srv_ip[] = "127.0.0.1";
    char clt_msg[M_MAX_BUFF_SIZE] = "Hello, Server!";

    clt_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (clt_sock_fd == -1) {
        perror("Client socket creat failed.");
        return -1;
    }

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SERVER_PORT);
    srv_addr.sin_addr.s_addr = inet_addr(srv_ip);

    if (-1 == connect(clt_sock_fd, (struct sockaddr*)&srv_addr, sizeof(struct sockaddr))) {
        perror("Client connect error");
        return -1;
    }

    write(clt_sock_fd, (void*)clt_msg, M_MAX_BUFF_SIZE);

    char clt_rcv_msg[M_MAX_BUFF_SIZE];
    if (recv(clt_sock_fd, (void*) clt_rcv_msg, M_MAX_BUFF_SIZE, 0) == -1) {
        perror("Client recveive msg from server error");
        return -1;
    }
    printf("Server: %s\n", clt_rcv_msg);
    close(clt_sock_fd);
    return 0;
}