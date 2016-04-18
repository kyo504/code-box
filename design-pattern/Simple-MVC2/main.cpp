#include <iostream>
using namespace std;

#include "Application.h"

int main()
{
	cout << "Start main function..." << endl;

	Application* app = new Application();

	if (app->InitInstance())
		app->Run();

	app->ExitInstance();

	return 0;
}
