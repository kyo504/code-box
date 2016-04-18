#pragma once

#include <vector>
#include "control.h"

class View
{
public:
	View();
	virtual ~View();

	void AddControl(Control*);
	void Render();
	void PrepareView();
	std::vector<Control*>* GetControls();

private:
	std::vector<Control*> *m_cList;
};

