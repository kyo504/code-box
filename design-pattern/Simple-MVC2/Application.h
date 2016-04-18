#pragma once

#include "View.h"
#include "Controller.h"
#include "Model.h"

class Application
{
public:
	Application();
	virtual ~Application();

	bool InitInstance();
	void Run();
	int ExitInstance();

private:
	View* m_pView;
	Controller* m_pController;
	Model* m_pModel;
};

