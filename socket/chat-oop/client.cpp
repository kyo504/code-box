// Client

#include "Socket.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

char name[NAME_SIZE]="[Default]";
char message[BUF_SIZE];

void error_handling(const char* message);
void* send_message(void* arg);
void* recv_message(void* arg);

int main(int argc, char** argv)
{
	pthread_t snd_thread, rcv_thread;
	void* thread_result;

	if(argc!=4) {
		printf("Usage: %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}

	sprintf(name, "[%s]", argv[3]);

	Socket* sock = new Socket();
	printf("New socket is created. (id:%d)\n", sock->getSocket());
	
	if(sock->connect(argv[1], argv[2]) == -1) {
		error_handling("connect() error");
	} else {
		printf("Connection is successfully established...\n");
	}

	int sock_fd = sock->getSocket();

	pthread_create(&snd_thread, NULL, send_message, (void*)&sock_fd);
	pthread_create(&rcv_thread, NULL, recv_message, (void*)&sock_fd);

	pthread_join(snd_thread, &thread_result);
	pthread_join(rcv_thread, &thread_result);

	delete sock;
	return 0;
}

void error_handling(const char* message)
{
	printf("%s (%s)\n", message, strerror(errno));
	exit(1);
}

void* send_message(void* arg)
{
	int sock_fd = *((int*)arg);
	char name_message[NAME_SIZE+BUF_SIZE];
	Socket* sock = new Socket();
	while(1) {
		fgets(message, BUF_SIZE, stdin);
		if(!strcmp(message, "q\n")) {
			close(sock_fd);
			exit(0);
		}
		sprintf(name_message, "%s",message);
		sock->send(sock_fd, name_message, strlen(name_message));
	}
	delete sock;
}

void* recv_message(void* arg)
{
	int sock_fd = *((int*)arg);
	char name_message[NAME_SIZE+BUF_SIZE];
	Socket* sock = new Socket();
	int str_len;
	while(1) {
		str_len = sock->recv(sock_fd, name_message, NAME_SIZE+BUF_SIZE-1);
		if(str_len==-1) return (void*)1;
		name_message[str_len]=0;
		fputs(name_message, stdout);
	}
	delete sock;
}
