#include "Image.h"
#include <iostream>

Image::Image(std::string url)
:m_sURL("")
{
	SetURL(url);
}

Image::~Image()
{
}

void Image::Render()
{
	std::cout << "Image(" << m_sURL << ") is renderd" << std::endl;
}

void Image::SetURL(std::string url)
{
	m_sURL = url;
}

void Image::HandleEvent(EventType e, void* data)
{
	HandlerMap::iterator it = m_Handlers.find(e);
	if (it == m_Handlers.end()) {
		std::cout << "There is no handler attached to this control" << std::endl;
	}
	else {
		it->second(e, data);
	}
}