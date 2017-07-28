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
server(int readfd, int writefd)
{
	int     fd;
	ssize_t n;
	char    buff[MAXLINE];

	//read pathname from IPC channel
	printf("SERVER: read pathname from readfd\n");
	while ( (n = read(readfd, buff, MAXLINE)) == 0) 
		printf("SERVER: No content to read");
	buff[n] = '\0';

	if ( (fd = open(buff, O_RDONLY)) < 0) {
		//tell client failure
		snprintf(buff + n, sizeof(buff) - n, ": can't open %s\n", strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);
	}
	//open success
	while( (n = read(fd, buff, MAXLINE)) > 0)
		write(writefd, buff, n);
	close(fd);
}

int
main(int argc, char ** argv)
{
	int readfd, writefd;

	printf("SERVER: Begin to make fifo 1...\n");
	//create 2 fifos
	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)) {
	    printf("can't create %s", FIFO1);
	}
	printf("SERVER: Begin to make fifo 2...\n");
	if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
	    unlink(FIFO1);
	    printf("can't create %s", FIFO2);
	}
	printf("SERVER: Read & Write\n");
	readfd = open(FIFO1, O_RDONLY, 0);
   	writefd = open(FIFO2, O_WRONLY, 0);
	server(readfd, writefd);
	exit(0);
}
