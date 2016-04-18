#include "Controller.h"


Controller::Controller(View* v)
:m_pView(v)
{
}


Controller::~Controller()
{
}

View* Controller::GetView()
{
	return m_pView;
}