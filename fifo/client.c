#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "fifo.h"

#define MAXLINE 256

void
client(int readfd, int writefd)
{
	size_t    len;
	ssize_t   n;
	char      buff[MAXLINE];

	//read pathname
	printf("CLIENT: Pls input pathname to read\n");
	fgets(buff, MAXLINE, stdin);
	len = strlen(buff);
	if(buff[len - 1] == '\n')
		--len;

	//write pathname to IPC
	write(writefd, buff, len);

	//read from IPC, write to standard output
	while( (n = read(readfd, buff, MAXLINE)) > 0)
	    write(STDOUT_FILENO, buff, n);
}

int
main(int argc, char ** argv)
{
	int     readfd, writefd;
        writefd = open(FIFO1, O_WRONLY, 0);
	readfd = open(FIFO2, O_RDONLY, 0);
	client(readfd, writefd);
	close(readfd);
	close(writefd);

	unlink(FIFO1);
	unlink(FIFO2);	
	exit(0);
}
