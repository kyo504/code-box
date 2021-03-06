#include "Controller.h"

Controller::Controller(View* v, Model* m)
:m_pView(v),
m_pModel(m)
{
}


Controller::~Controller()
{
}


void Controller::AddObserver(IObserver* observer, EventType eType)
{
	m_observers[eType].push_back(observer);
}

void Controller::RemoveObserver(IObserver* observer, EventType eType)
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
void Controller::SendEvent(EventType event, void* data)
{
	ObserverList& observers = m_observers[event];
	for (ObserverList::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		IObserver* observer = *it;
		observer->HandleEvent(event, data); // here an observer receive the event
	}
}

View* Controller::GetView()
{
	return m_pView;
}

Model* Controller::GetModel()
{
	return m_pModel;
}