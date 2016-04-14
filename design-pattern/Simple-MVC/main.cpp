#include <stdio.h>
#include <stdlib.h>


class Object
{
public:
	Object() {}
	virtual ~Object() {}

};

class Button : public Object
{
public:
	Button() {}
	virtual ~Button() {}

	void onClick() {
		printf("Button is clicked...\n");
	}
};

class View
{
public:

};

class Controller
{
public:

};

class Model
{
public:

};

int main()
{


	return 0;
}