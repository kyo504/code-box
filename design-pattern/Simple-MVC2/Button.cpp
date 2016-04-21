#include "Button.h"

#include <iostream>

Button::Button(std::string text)
:m_sText(text),
m_bDisabled(false)
{
}


Button::~Button()
{
}

void Button::Render()
{
	std::cout << "Button(" << m_sText << ") is rendered" << std::endl;
}

void Button::SetText(std::string text)
{
	std::cout << "Text is chaged from " << m_sText << " to " << text << std::endl;
	m_sText = text;
}

void Button::HandleEvent(EventType e, void* data)
{
	HandlerMap::iterator it = m_Handlers.find(e);
	if (it == m_Handlers.end()) {
		std::cout << "There is no handler attached to this control" << std::endl;
	}
	else {
		it->second(e, data);
	}
}

void Button::SetDisabled(bool bDisabled)
{
	m_bDisabled = bDisabled;
}

bool Button::GetDisabled()
{
	return m_bDisabled;
}
