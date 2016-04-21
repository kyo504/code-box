#include "Control.h"


Control::Control()
{
}


Control::~Control()
{
}

void Control::AddHandler(EventType e, std::function<void(EventType, void*)> pFP)
{
	m_Handlers.insert(std::pair<EventType, std::function<void(EventType, void*)>>(e, pFP));
}