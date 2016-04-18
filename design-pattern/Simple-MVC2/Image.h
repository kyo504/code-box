#pragma once

#include "Control.h"
#include <string>

class Image :
	public Control
{
public:
	Image(std::string url);
	virtual ~Image();

	virtual void Render();
	void SetURL(std::string url);

private:
	std::string m_sURL;
};

