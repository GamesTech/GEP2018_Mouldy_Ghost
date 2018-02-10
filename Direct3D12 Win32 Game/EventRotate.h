#pragma once
#include "EventSystem.h"
class EventRotate :
	public EventSystem
{
public:
	EventRotate();
	~EventRotate();
	virtual void run(ImageGO2D* self) override;
};

