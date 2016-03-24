// Server
#include "Socket.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "errno.h"
#include "string.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <vector>
#include <algorithm>
#include <pthread.h>

#define BUF_SIZE 100

using namespace std;

void error_handling(const char* message);
void* clnt_connection(void* arg);
void send_message(char* message, int len);

vector<int>	clnt_socks;
pthread_mutex_t mutx;

int main(int argc, char** argv)
{
	pthread_t thread;

	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	Socket* serv_sock = new Socket();
	printf("New socket is created. (id:%d)\n", serv_sock->getSocket());

	if(serv_sock->bind(NULL, argv[1]) == -1) {
		error_handling("bind() error");
	} else {
		printf("bind is done...\n");
	}

	if(serv_sock->listen() == -1) {
		error_handling("listen() error");
	} else {
		printf("listen is done...\n");
	}

	while(1) {

		printf("Waiting for new connection request...\n");
		int clnt_sock = serv_sock->accept();
		
		pthread_mutex_lock(&mutx);
		clnt_socks.push_back(clnt_sock);
		pthread_mutex_unlock(&mutx);
		printf("Total connected sockets : %d\n", (int)clnt_socks.size());

		pthread_create(&thread, NULL, clnt_connection, (void*)&clnt_sock);
		printf("New connection is established...\n");
	}

	delete serv_sock;

	return 0;
}

void error_handling(const char* message)
{
	printf("%s (%s)\n", message, strerror(errno));
	exit(1);
}

void* clnt_connection(void* arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0;
	char message[BUF_SIZE];
	Socket* sock = new Socket();

	while( (str_len=sock->recv(clnt_sock, message, sizeof(message))) != 0 ) {
		send_message(message, str_len);
	}

	pthread_mutex_lock(&mutx);
	vector<int>::iterator it = find(clnt_socks.begin(), clnt_socks.end(), clnt_sock);
	clnt_socks.erase(it);
	pthread_mutex_unlock(&mutx);
	printf("A total number of connections : %d \n", (int)clnt_socks.size());

	::close(clnt_sock);
	delete sock;

	return (void*)1;
}

void send_message(char* message, int len)
{
	Socket* sock = new Socket();

	// Broadcast message to all clients
	pthread_mutex_lock(&mutx);
	for(vector<int>::iterator iter=clnt_socks.begin(); iter!= clnt_socks.end(); ++iter) {
		sock->send(*iter, message, len);
	}
	pthread_mutex_unlock(&mutx);

	delete sock;
}

