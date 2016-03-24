#include "Room.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

#include "Socket.h"

#define BUF_SIZE 100

Room::Room()
:mID(-1),
 mType(ROOM_PUBLIC)
{

}

Room::Room(int roomID)
: mType(ROOM_PUBLIC)
{
	mID = roomID;
}

Room::~Room()
{

}

void Room::setID(int roomID)
{
	mID = roomID;
}

int Room::getID()
{
	return mID;
}

void Room::setType(ROOM_TYPE type)
{
	mType = type;
}

ROOM_TYPE Room::getType()
{
	return mType;
}

void Room::join(int sockID)
{
	mClientSocks.push_back(sockID);

	Socket* sock = new Socket();
	int str_len;

	char message[BUF_SIZE];

	printf("Start...\n");

	while( (str_len = sock->recv(sockID, message, sizeof(message))) != 0) {
		for(vector<int>::iterator iter = mClientSocks.begin(); iter != mClientSocks.end(); ++iter) {
			sock->send(*iter, message, str_len);
		}
	}

	delete sock;
}

void Room::leave(int sockID)
{
	vector<int>::iterator iter;
	iter = find(mClientSocks.begin(), mClientSocks.end(), sockID);
	mClientSocks.erase(iter);
}

int Room::getCount()
{
	return (int)mClientSocks.size();
}
