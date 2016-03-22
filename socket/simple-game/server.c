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

void error_handling(char* message);
void z_handler(int sig);
int who_win(int a, int b);

int main(int argc, char** argv)
{
	int fd1[2], fd2[2];

	char buffer[BUF_SIZE];
	char intro[]="Choose one(0: Scissor, 1:Rock, 2:Paper) : ";
	char win[]="Congratulation, you win.\n";
	char lose[]="Sorry, you lose\n";
	char no_winner[]="Draw, no winner\n";

	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	struct sigaction act;
	int str_len, state, addr_size;
	pid_t pid;

	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// Create two pipes
	if(pipe(fd1)<0 || pipe(fd2)<0) {
		error_handling("pipe() error");
	}

	act.sa_handler=z_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	state=sigaction(SIGCHLD, &act, 0);
	if(state!=0) {
		error_handling("sigaction() error");
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	printf("Server socket is created(id:%d)\n", serv_sock);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	if(listen(serv_sock, 5) == -1) {
		error_handling("listen() error");
	}

	while(1) {

		addr_size=sizeof(clnt_addr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_size);
		if(clnt_sock == -1)
			continue;

		if( (pid=fork()) == -1 ) {

			close(clnt_sock);
			continue;

		} else if( pid>0 ) {

			int result;
			puts("[Parent Process] Continues...\n");
			close(clnt_sock);

			write(1, intro, sizeof(intro));
			read(0, buffer, BUF_SIZE);	// Receive choice from server
			read(fd1[0], &buffer[1], BUF_SIZE-1); // Receive choice from client

			result = who_win(buffer[0], buffer[1]);
			if(result==0) {

				write(1, no_winner, sizeof(no_winner));
				write(fd2[1], no_winner, sizeof(no_winner));

			} else if(result==1) {

				write(1, win, sizeof(win));
				write(fd2[1], win, sizeof(win));

			} else {

				write(1, lose, sizeof(lose));
				write(fd2[1], lose, sizeof(lose));

			}

		} else {
			puts("[Child Process] Starts....\n");
			close(serv_sock);

			write(clnt_sock, intro, sizeof(intro));
			read(clnt_sock, buffer, BUF_SIZE);
			write(fd1[1], buffer, 1);
			str_len=read(fd2[0], buffer, BUF_SIZE);
			write(clnt_sock, buffer, str_len);

			puts("[Child Process] Close child process...\n");
			close(clnt_sock);
			exit(0);
		}
	}

	return 0;
}

int who_win(int a, int b)
{
	//printf("%d, %d\n", a, b);
	if(a==b)
		return 0;
	else if(a%3==(b+1)%3)
		return 1;
	else
		return -1;
}

void z_handler(int sig)
{
	pid_t pid;
	int rtn;

	pid=waitpid(-1, &rtn, WNOHANG);
	printf("Destroyed zombie process ID : %d \n", pid);
	printf("Returned data : %d \n\n", WEXITSTATUS(rtn));
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
