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

int main()
{
    int srv_sock_fd, clt_sock_fd;
    struct sockaddr_in srv_addr;
    struct sockaddr_in clt_addr;

    srv_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (srv_sock_fd == -1) {
        perror("Server socket creat failed.");
        return -1;
    }

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SERVER_PORT);
    srv_addr.sin_addr.s_addr = INADDR_ANY;

    if (-1 == bind(srv_sock_fd, (struct sockaddr*)&srv_addr, sizeof(struct sockaddr))) {
        perror("Server bind error");
        return -1;
    }

    if (listen(srv_sock_fd, 10) == -1) {
        perror("Server listen error");
        return -1;
    }

    while (1) {
        socklen_t sin_size = sizeof(struct sockaddr_in);
        clt_sock_fd = accept(srv_sock_fd, (struct sockaddr*) &srv_addr, &sin_size);
        if (-1 == clt_sock_fd) {
            perror("Server accept error");
            return -1;
        }

        printf("\nServer receive connection from %s...\n", (char*)inet_ntoa(clt_addr.sin_addr));

        if (0 != fork()) {
            char buff[M_MAX_BUFF_SIZE];
            
            if (read(clt_sock_fd, buff, M_MAX_BUFF_SIZE) < 0) {
                perror("Server read client error");
                continue;
            }
            printf("Clent: %s", buff);

            char rsp_msg[M_MAX_BUFF_SIZE] = "Congrats, Successed!";
            if (send(clt_sock_fd, (void*)rsp_msg, M_MAX_BUFF_SIZE, 0) == -1) {
                perror("Server send msg to client error");
            }
            close(clt_sock_fd);
        }
        close(clt_sock_fd);
    }
    return 0;
}