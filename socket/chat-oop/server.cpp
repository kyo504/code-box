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
#include <string>
#include <algorithm>
#include <pthread.h>
#include <sstream>
#include <iostream>

#include "Room.h"

#define BUF_SIZE 100

using namespace std;

void error_handling(const char* message);
void* clnt_connection(void* arg);
void send_message(char* message, int len);
string int2str(int n);

vector<int>	clnt_socks;
pthread_mutex_t mutx;
vector<Room*> room_list;

static int roomID = 100;

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
		printf("1111111111\n");
		
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

void display_menu(int clnt_sock)
{
	Socket* sock = new Socket();
	string str;

	str = "Room List\n";
	sock->send(clnt_sock, (char*)str.c_str(), str.length());
	vector<Room*>::iterator iter = room_list.begin();

	if((int)room_list.size() < 1) {
		str = "There is no chat room!\n";
		sock->send(clnt_sock, (char*)str.c_str(), str.length());
	} else {
		for(; iter != room_list.end(); ++iter) {
			//string s = to_string((*iter)->getID());
			string s = int2str((*iter)->getID());
			s = s + '\n';
			sock->send(clnt_sock, (char*)s.c_str(), s.length()); 
		}
	}

	str = "1. Create a chat room\n";
	sock->send(clnt_sock, (char*)str.c_str(), str.length());
	str = "2. Enter number to join a room\n";
	sock->send(clnt_sock, (char*)str.c_str(), str.length());
	str = "Select an option :\n";
	sock->send(clnt_sock, (char*)str.c_str(), str.length());
	str = "xxxxxxxxxxxxxxxxxxxx1\n";
	sock->send(clnt_sock, (char*)str.c_str(), str.length());

	delete sock;

	for_each(room_list.begin(), room_list.end(), [](Room* ptr){ delete ptr; });
}

void* clnt_connection(void* arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0;
	char message[BUF_SIZE];
	Socket* sock = new Socket();

	display_menu(clnt_sock);

	int choice;

	while( (str_len=sock->recv(clnt_sock, message, sizeof(message))) != 0 ) {
		message[str_len]=0;
		choice = atoi(message);
		printf("Choice: %d\n", choice);
		if(choice == 1) {
			Room* rm = new Room(roomID++);
			room_list.push_back(rm);
		} else {
			printf("break....\n");
			break;
		}
		display_menu(clnt_sock);
	}
	
	printf("choice %d\n", choice);
	vector<Room*>::iterator rm_iter = room_list.begin();
	for(; rm_iter != room_list.end(); ++rm_iter) {
		if((*rm_iter)->getID() == choice) {
			(*rm_iter)->join(clnt_sock);
		}
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

string int2str(int n)
{
	stringstream s;
	s << n;
	return s.str();
}
