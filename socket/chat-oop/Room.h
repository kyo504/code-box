#ifndef ROOM_H_
#define ROOM_H_

#include <vector>
#include <algorithm>

using namespace std;

enum ROOM_TYPE {
	ROOM_PUBLIC,
	ROOM_PRIVATE,
	ROOM_MAX
};

class Room {
public:
	Room();
	Room(int roomID);
	virtual ~Room();

	int getID();
	void setID(int roomID);
	void setType(ROOM_TYPE type);
	ROOM_TYPE getType();
	void join(int sockID);
	void leave(int sockID);
	int getCount();
	
private:
	int mID;	// room ID
	vector<int> mClientSocks;
	ROOM_TYPE mType;	
};

#endif /* ROOM_H_ */
