#pragma once

#include <vector>
#include <map>
#include "IObserver.h"
#include "IObservable.h"
#include "View.h"
#include "Model.h"

class Controller : public IObservable
{
public:
	Controller(View* v, Model* m);
	virtual ~Controller();

	// this is simplist, to say the least...
	virtual void AddObserver(IObserver* observer, EventType eType);
	virtual void RemoveObserver(IObserver* observer, EventType eType);

	// here we send the event, it will be catched by observers
	// note : often this type of system is "buffered", but here we will process it immediatly as it's a simple example
	void SendEvent(EventType event, void* data);
	View* GetView();
	Model* GetModel();

private:
	typedef std::vector<IObserver*> ObserverList;
	typedef std::map< EventType, ObserverList > ObserversTable;
	ObserversTable m_observers; // we have observers for each event type
	View* m_pView;
	Model* m_pModel;
};