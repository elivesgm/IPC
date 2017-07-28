#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

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
	int      pipe1[2], pipe2[2];
	pid_t    childpid;

	pipe(pipe1);
	pipe(pipe2);

	printf("PARENT: Begin to fork child...\n");
	if( (childpid = fork()) == 0) {
		//child
		printf("CHILD: Call server...\n");
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}
	//parent
	printf("PARENT: Call client...\n");
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0],pipe1[1]);

	waitpid(childpid, NULL, 0);//Wait for child to terminate
	exit(0);
}
