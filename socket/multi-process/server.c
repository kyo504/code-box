#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);
void z_handler(int sig);

int main(int argc, char** argv)
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	struct sigaction act;
	int addr_size, str_len, state;
	pid_t pid;
	char message[BUF_SIZE];

	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	act.sa_handler=z_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	state=sigaction(SIGCHLD, &act, 0); // Register signal handler
	if(state != 0) {
		puts("sigaciton() error");
		exit(1);
	}
	
	// Create a socket
	// PF_INET : IPv4 Internet Protocol
	// SOCK_STREAM : Provides sequenced, reliable, two-way, connection-based byte streams
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	// Reset memory for serv_addr
	memset(&serv_addr, 0, sizeof(serv_addr));
	// Fill out each properties
	// AF_INET : IPv4 Internet Protocol
	// INADDR_ANY : Address is automatically assigned
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	// atoi : Ascii to Integer
	serv_addr.sin_port=htons(atoi(argv[1]));

	// Address information is assigend to the given socket
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	printf("Wait for connection...\n");	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	while(1) {
		addr_size=sizeof(clnt_addr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_size);
		if(clnt_sock==-1)
			continue;

		if( (pid=fork()) == -1 ) {
			close(clnt_sock);
			continue;
		} else if( pid > 0) {
			printf("Connection is created(pid:%d)\n", pid );
			close(clnt_sock);
			continue;
		} else {
			printf("Start child process(pid:%d)\n", pid);
			close(serv_sock);

			while( (str_len=read(clnt_sock, message, BUF_SIZE)) != 0) {
				write(clnt_sock, message, str_len);
				write(1, message, str_len);
			}
			puts("Disconnected...");
			close(clnt_sock);
			exit(0);
		}
	}

	close(clnt_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void z_handler(int sig)
{
	pid_t pid;
	int rtn;

	pid=waitpid(-1, &rtn, WNOHANG);
	printf("Destoryed zombie process ID : %d \n", pid);
	printf("Returned data : %d \n\n", WEXITSTATUS(rtn));
}
