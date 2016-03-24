#include "Socket.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


Socket::Socket()
:mSocket(-1)
{
	mSocket = socket(PF_INET, SOCK_STREAM, 0);
}

Socket::~Socket() {
	close();
}

int Socket::getSocket()
{
	return mSocket;
}

int Socket::connect(char* ip, char* port)
{
	if( !ip || !port ) return -1;

	printf("IP : %s, PORT: %s\n", ip, port);

	struct sockaddr_in addr;
	memset(&addr, 0x0, sizeof(addr));
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= inet_addr(ip);
	addr.sin_port			= htons(atoi(port));

	return ::connect(mSocket, (struct sockaddr*)&addr, sizeof(addr));
}

void Socket::close()
{
	::close(mSocket);
}

int Socket::bind(char* ip, char* port)
{
	printf("IP: %s, PORT: %s\n", ip, port);

	struct sockaddr_in addr;
	memset(&addr, 0x0, sizeof(addr));
	addr.sin_family			= AF_INET;
	//addr.sin_addr.s_addr	= (ip == NULL) ? htonl(INADDR_ANY) : inet_addr(ip);
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	addr.sin_port			= htons(atoi(port));

	int optvalue = 1;
	int optlen = sizeof(optvalue);
	::setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &optvalue, optlen);

	return ::bind(mSocket, (struct sockaddr*)&addr, sizeof(addr));
}

int Socket::listen()
{
	return ::listen(mSocket, 5);
}

int Socket::accept()
{
	struct sockaddr_in addr;
	memset(&addr, 0x0, sizeof(addr));
	socklen_t client_len = sizeof(struct sockaddr_in);
	printf("[%s] socket id: %d, length: %d\n", __FUNCTION__, mSocket, (int)client_len);
	return ::accept(mSocket, (struct sockaddr*)&addr, &client_len);	
}

int Socket::send(char* data, int size)
{
	return ::write(mSocket, data, size);
}

int Socket::send(int sock, char* data, int size)
{
	return ::write(sock, data, size);
}

int Socket::recv(char* data, int size)
{
	return ::read(mSocket, data, size);
}

int Socket::recv(int sock, char* data, int size)
{
	return ::read(sock, data, size);
}

