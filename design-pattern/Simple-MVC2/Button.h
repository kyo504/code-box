#pragma once

#include "Control.h"
#include <string>

class Button :
	public Control
{
public:
	Button(std::string text);
	virtual ~Button();

	void SetText(std::string text);
	void SetDisabled(bool bDisabled);
	bool GetDisabled();

	virtual void Render();
	virtual void HandleEvent(EventType e, void* data);

private:
	std::string m_sText;
	bool m_bDisabled;
};
