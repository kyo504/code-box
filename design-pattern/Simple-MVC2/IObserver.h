#pragma once

#include "EventType.h"

class IObserver
{
public:
	virtual void HandleEvent(EventType e, void* data) = 0;
	virtual ~IObserver();
};

