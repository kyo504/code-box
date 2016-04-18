#include "Button.h"

#include <iostream>

Button::Button(std::string text)
:m_sText("")
{
	SetText(text);
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
	m_sText = text;
}