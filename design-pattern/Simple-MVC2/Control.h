#pragma once

#include "IObserver.h"
#include <map>
#include <functional>

class Control : public IObserver
{
protected:
	typedef std::map<EventType, std::function<void(EventType, void*)>> HandlerMap;
	HandlerMap m_Handlers;

public:
	Control();
	virtual ~Control();

	virtual void Render() = 0;
	//void AddHandler(EventType e, void(*pFP)(EventType, void*));
	void AddHandler(EventType e, std::function<void(EventType, void*)>);

};
