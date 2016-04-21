#pragma once

#include "Control.h"
#include <string>

class Image :
	public Control
{
public:
	Image(std::string url);
	virtual ~Image();

	void SetURL(std::string url);

	virtual void Render();
	virtual void HandleEvent(EventType e, void* data);

private:
	std::string m_sURL;
};

