#pragma once

#include "View.h"

class Controller
{
public:
	Controller(View*);
	virtual ~Controller();

	View* GetView();

private:
	View* m_pView;
};

