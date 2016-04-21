#include "EventHandler.h"

EventHandler* EventHandler::sInstance = NULL;

EventHandler* EventHandler::GetInstance()
{
	if (sInstance == NULL) {
		sInstance = new EventHandler();
	}
	return sInstance;
}

/*
EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}
/**/

void EventHandler::AddObserver(IObserver* observer, EventType eType)
{
	m_observers[eType].push_back(observer);
}

void EventHandler::RemoveObserver(IObserver* observer, EventType eType)
{
	ObserversTable::iterator it = m_observers.find(eType);
	if (it != m_observers.end()) {
		ObserverList::iterator iter = std::find(it->second.begin(), it->second.end(), observer);
		if (iter != it->second.end()) {
			it->second.erase(iter);
		}
	}
}

// here we send the event, it will be catched by observers
// note : often this type of system is "buffered", but here we will process it immediatly as it's a simple example
void EventHandler::SendEvent(EventType event, void* data)
{
	ObserverList& observers = m_observers[event];
	for (ObserverList::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		IObserver* observer = *it;
		observer->HandleEvent(event, data); // here an observer receive the event
	}
}
