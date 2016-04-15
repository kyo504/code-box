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


class Object
{
public:
	Object() {}
	virtual ~Object() {}

};

class Button : public Object
{
public:
	Button() {}
	virtual ~Button() {}

	void onClick() {
		printf("Button is clicked...\n");
	}
};

class Controller;

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

	void Update() {
		cout << "View UPdater Called ......";
	}

private:
	Controller *mController;
};

class Controller
{
public:
	Controller(ISubject* subject) {
		mSubject = subject;
	}

	void ModifyAge(int newAge) {
		dynamic_cast<>(mSubject)
		(dynamic_cast(mSubject))->SetAge(newAge);
	}

	void Register(IObserver *viewobj) {
		mSubject->Register(viewobj);
	}

private:
	ISubject *mSubject;
};

class Model : public ISubject
{
public:
	virtual void Register(IObserver *observingObject) {
		_observerMap.push_back(observingObject);
	}

	virtual void UnRegister() {
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