#pragma once

#include <vector>
#include <map>
#include "IObserver.h"

class EventHandler
{
public:
	// this is simplist, to say the least...
	virtual void AddObserver(IObserver* observer, EventType eType);
	virtual void RemoveObserver(IObserver* observer, EventType eType);

	// here we send the event, it will be catched by observers
	// note : often this type of system is "buffered", but here we will process it immediatly as it's a simple example
	void SendEvent(EventType event, void* data);

	static EventHandler* GetInstance();

private:
	typedef std::vector<IObserver*> ObserverList;
	typedef std::map< EventType, ObserverList > ObserversTable;
	ObserversTable m_observers; // we have observers for each event type

	static EventHandler* sInstance;
};