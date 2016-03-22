#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>

#define BUF_SIZE 100

void* clnt_connection(void* arg);
void send_message(char* message, int len);
void error_handling(char* message);

int clnt_number=0;
int clnt_socks[10];
pthread_mutex_t mutx;

int main(int argc, char** argv)
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	pthread_t thread;

	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if(pthread_mutex_init(&mutx, NULL))
		error_handling("mutex init error");

	// Create a socket for server
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	printf("Server socket is created(id:%d)\n", serv_sock);

	// Set address information
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	serv_addr.sin_port			= htons(atoi(argv[1]));

	// Assgin address information to server socket
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");
	printf("Bind is done\n");

	// The listen() function basically sets a flag in the internal socket structure 
	// marking the socket as a passive listening socket, one that you can call accept on.
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	printf("Listen is done\n");

	while(1) {
		clnt_addr_size=sizeof(clnt_addr);
		// Accept connection request from clients
		printf("Waiting for connection request...\n");
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		printf("Accept is done(id:%d)\n", clnt_sock);

		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_number++]=clnt_sock;
		pthread_mutex_unlock(&mutx);

		pthread_create(&thread, NULL, clnt_connection, (void*)&clnt_sock);
		printf("New Connection, clitn IP : %s \n", inet_ntoa(clnt_addr.sin_addr));
	}

	return 0;
}

/*
 * @brief : starting point when thread starts
 */
void* clnt_connection(void* arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0;
	char message[BUF_SIZE];
	int i;

	while( (str_len=read(clnt_sock, message, sizeof(message))) != 0 )
		send_message(message, str_len);

	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_number; i++) {

		if(clnt_sock == clnt_socks[i]) {
			for(; i<clnt_number-1; i++)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_number--;
	pthread_mutex_unlock(&mutx);

	close(clnt_sock);
	return 0;
}

void send_message(char* message, int len)
{
	int i;
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_number; i++)
		write(clnt_socks[i], message, len);
	pthread_mutex_unlock(&mutx);
}

void error_handling(char* message)
{
	printf("%s (%s)\n", strerror(errno));
	exit(1);
}

