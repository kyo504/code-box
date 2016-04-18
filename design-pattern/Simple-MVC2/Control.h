#pragma once
class Control
{
public:
	Control();
	virtual ~Control();

	virtual void Render() = 0;
};

