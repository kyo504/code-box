#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <list>
using namespace std;

class ISubject;

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update(ISubject* theChangedSubject) = 0;

protected:
	IObserver() {}
};

class ISubject
{
public:
	virtual ~ISubject() {
		if (!_observers) {
			delete _observers;
		}
	};
	virtual void Attach(IObserver* o) {
		_observers->push_back(o);
	}
	virtual void Detach(IObserver* o) {
		_observers->remove(o);
	}
	virtual void Notify() {
		list<IObserver*>::iterator it = _observers->begin();
		for (; it != _observers->end(); ++it) {
			(*it)->Update(this);
		}
	}
protected:
	ISubject():_observers(0) {
		_observers = new list<IObserver*>;
	}

private:
	list<IObserver*> *_observers;
};

class ClockTimer : public ISubject
{
public:
	ClockTimer() : _hour(0), _minute(0), _second(0) {}

	virtual int GetHour() {
		return _hour;
	}
	virtual int GetMinute() {
		return _minute;
	}
	virtual int GetSecond() {
		return _second;
	}

	void Tick() {

		// Update time information

		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		_hour = static_cast<int>(timeinfo->tm_hour);
		_minute = static_cast<int>(timeinfo->tm_min);
		_second = static_cast<int>(timeinfo->tm_sec);

		Notify();
	}
private:
	int _hour;
	int _minute;
	int _second;
};

class Widget
{
public:
	virtual void Draw() = 0;
};

class DigitalClock : public Widget, public IObserver
{
public:
	DigitalClock(ClockTimer* s) {
		_subject = s;
		_subject->Attach(this);
	}
	virtual ~DigitalClock() {};

	virtual void Update(ISubject* theChangedSubject) {
		if (theChangedSubject == _subject) {
			Draw();
		}
	}
	virtual void Draw() {
		int hour = _subject->GetHour();
		int minute = _subject->GetMinute();
		int second = _subject->GetSecond();

		// Display...
		printf("[Digital Clock] %02d:%02d:%02d\n", hour, minute, second);
	}

private:
	ClockTimer* _subject;
};

class AnalogClock : public Widget, public IObserver
{
public:
	AnalogClock(ClockTimer* s) {
		_subject = s;
		_subject->Attach(this);
	}
	virtual ~AnalogClock() {};

	virtual void Update(ISubject* theChangedSubject) {
		if (theChangedSubject == _subject) {
			Draw();
		}
	}
	virtual void Draw() {
		int hour = _subject->GetHour();
		int minute = _subject->GetMinute();
		int second = _subject->GetSecond();

		// Display...
		printf("[Analog Clock] %02d:%02d:%02d\n", hour, minute, second);
	}

private:
	ClockTimer* _subject;
};

int main()
{
	ClockTimer* timer = new ClockTimer();
	AnalogClock* aClock = new AnalogClock(timer);
	DigitalClock* dClock = new DigitalClock(timer);

	while (1) {
		timer->Tick();
		Sleep(1000);
	}

	return 0;
}