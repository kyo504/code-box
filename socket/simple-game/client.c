#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char** argv)
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_addr;

	if(argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		error_handling("socket() error");
	}
	printf("Server socket is created(id:%d)\n", sock);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error");
	}

	// Get intro message from server
	str_len=read(sock, message, BUF_SIZE-1);
	message[str_len]=0;
	fputs(message, stdout);
	fflush(stdout);

	// Read user input and send it to server
	str_len=read(0, message, BUF_SIZE);
	write(sock, message, strlen(message));

	// Get result of comparision
	str_len=read(sock, message, BUF_SIZE-1);
	message[str_len]=0;
	printf("%s\n", message);

	close(sock);

	return 0;
}

void error_handling(char* message)
{
	printf("%s(%s)\n", message, strerror(errno));
	exit(1);
}
