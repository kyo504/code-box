#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;


// http://cplusplusbench.blogspot.kr/2007/05/mvc-simple-implementation.html

class IObserver
{
public:
	virtual void Update() = 0;
};

class ISubject
{
public:
	virtual void Register(IObserver*) = 0;
	virtual void Unregister() = 0;
};

class Model : public ISubject
{
public:
	virtual void Register(IObserver *observingObject) {
		_observerMap.push_back(observingObject);
		cout << "Total number of observers: " << static_cast<int>(_observerMap.size()) << endl;
	}

	virtual void Unregister() {
		// TBD
	}

	int GetAge() {
		return age;
	}
	void SetAge(int newAge) {
		age = newAge;
		NotifyObserver();
	}

private:
	int age;
	vector<IObserver*> _observerMap;
	void NotifyObserver(){
		for (int i = 0; i < static_cast<int>(_observerMap.size()); i++) {
			_observerMap[i]->Update();
		}
	}
};

class Controller : public ISubject
{
public:
	Controller(ISubject* subject) {
		mSubject = subject;
	}

	void ModifyAge(int newAge) {
		(dynamic_cast<Model*>(mSubject))->SetAge(newAge);
	}

	virtual void Register(IObserver *viewobj) {
		mSubject->Register(viewobj);
	}

	virtual void Unregister() {
		// TBD
	}

private:
	ISubject *mSubject;
};

class View : public IObserver
{
public:
	View(Controller *controller) {
		mController = controller;
		controller->Register(this);
	}

	void EnterAge() {
		cout << "Enter Age";
		int x = 0;
		cin >> x;
		mController->ModifyAge(x);
	}

	virtual void Update() {
		cout << "View Updater Called ......";
	}

private:
	Controller *mController;
};

int main()
{
	/*
	View* view = new View();
	Controller* controller = new Controller();
	Model* model = new Model();
	/**/

	Model *model = new Model();
	Controller * controller = new Controller(model);
	View *view = new View(controller);

	view->EnterAge();



	return 0;
}