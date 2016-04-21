#include "View.h"
#include "Button.h"
#include "Image.h"
#include <string>
#include <iostream>

View::View()
:m_cList(0)
{
	m_cList = new std::vector<Control*>;
}

View::~View()
{
	if (m_cList){
		for (std::vector<Control*>::iterator it = m_cList->begin(); it != m_cList->end(); ++it)
		{
			delete (*it);
		}
		m_cList->clear();

		delete m_cList;
		m_cList = NULL;
	}
}

void View::AddControl(Control* c)
{
	m_cList->push_back(c);
}

void View::Render()
{
	std::vector<Control*>::iterator it = m_cList->begin();
	for (; it != m_cList->end(); ++it) {
		(*it)->Render();
	}
}

void View::PrepareView()
{
	Button* pBtn1 = new Button(std::string("Button 1"));
	pBtn1->AddHandler(EVENT_ON_CLICK, [pBtn1](EventType e, void* data){
		std::cout << "BUTTON EVENT_A : " << *(static_cast<std::string*>(data)) << std::endl;

		pBtn1->SetText(std::string("hjaha"));
	});
	AddControl(pBtn1);

	Button* pBtn2 = new Button(std::string("Button 2"));
	pBtn2->AddHandler(EVENT_ON_HIDE, [pBtn2](EventType e, void* data){
		std::cout << "BUTTON EVENT_B : " << *(static_cast<std::string*>(data)) << std::endl;
	});
	AddControl(pBtn2);

	AddControl(new Image(std::string("/path/to/url/bird.png")));
	AddControl(new Image(std::string("/path/to/url/dog.png")));
}

std::vector<Control*>* View::GetControls()
{
	return m_cList;
}