#include "Application.h"

#include "Button.h"
#include <iostream>

Application::Application()
{
}

Application::~Application()
{
}

bool Application::InitInstance()
{
	this->m_pView = new View();
	this->m_pController = new Controller(this->m_pView);
	this->m_pModel = new Model();

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
		} else {
			std::cout << "Not Null" << std::endl;
		}
	}
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
