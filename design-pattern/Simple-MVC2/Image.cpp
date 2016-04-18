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