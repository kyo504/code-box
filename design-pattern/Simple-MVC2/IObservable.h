#pragma once

#include "IObserver.h"

class IObservable
{
public:
	virtual void AddObserver(IObserver* observer, EventType eType) = 0;
	virtual void RemoveObserver(IObserver* observer, EventType eType) = 0;

	virtual ~IObservable() {};
};

