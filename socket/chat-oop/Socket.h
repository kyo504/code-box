#ifndef SOCKET_H_
#define SOCKET_H_

class Socket {
public:
	Socket();
	virtual ~Socket();

	int getSocket();
	int bind(char* ip, char* port);
	int connect(char* ip, char* port);
	int listen();
	int accept();
	void close();
	int send(char* data, int size);
	int send(int sock, char* data, int size);
	int recv(char* data, int size);
	int recv(int sock, char* data, int size);

private:
	int mSocket;
};

#endif /* SOCKET_H_ */
