#include "View.h"
#include "Button.h"
#include "Image.h"
#include <string>

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
	AddControl(new Button(std::string("Button 1")));
	AddControl(new Button(std::string("Button 2")));
	AddControl(new Image(std::string("/path/to/url/bird.png")));
	AddControl(new Image(std::string("/path/to/url/dog.png")));
}

std::vector<Control*>* View::GetControls()
{
	return m_cList;
}