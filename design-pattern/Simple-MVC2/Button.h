#pragma once

#include "Control.h"
#include <string>

class Button :
	public Control
{
public:
	Button(std::string text);
	virtual ~Button();

	void Render();
	void SetText(std::string text);

private:
	std::string m_sText;
};
