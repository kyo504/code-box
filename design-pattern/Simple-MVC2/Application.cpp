#include "Application.h"

#include "Button.h"
#include "Image.h"
#include <iostream>
#include <string>

Application::Application()
{
}

Application::~Application()
{
}

bool Application::InitInstance()
{
	this->m_pView = new View();
	this->m_pModel = new Model();
	this->m_pController = new Controller(this->m_pView, this->m_pModel);

	m_pView->PrepareView();

	return true;
}

void Application::Run()
{
	m_pView->Render();

	// Change some properties...
	std::vector<Control*> *pControls = m_pView->GetControls();
	pControls->size();

	for (std::vector<Control*>::iterator it = pControls->begin(); it != pControls->end(); ++it) {
		Button* pBtn = dynamic_cast<Button*>(*it);
		if (pBtn == NULL) {
			std::cout << "Null" << std::endl;
			Image* pImg = dynamic_cast<Image*>(*it);
			m_pController->AddObserver(dynamic_cast<IObserver*>(pImg), EVENT_ON_HIDE);
		}
		else {
			std::cout << "Not Null" << std::endl;
			m_pController->AddObserver(dynamic_cast<IObserver*>(pBtn), EVENT_ON_CLICK);
		}
	}
	
	std::string strData1 = "Data for Event A";
	std::string strData2 = "Data for Event B";


	// Dispatch events
	m_pController->SendEvent(EVENT_ON_CLICK, (void*)(&strData1));
	m_pController->SendEvent(EVENT_ON_HIDE, (void*)(&strData2));
}

int Application::ExitInstance()
{
	if (m_pView) {
		delete m_pView;
	}

	if (m_pController) {
		delete m_pController;
	}

	if (m_pModel) {
		delete m_pModel;
	}

	return 1;
}
