#pragma once
#include "EventSystem.h"
#include "ImageGO2D.h"
class EventScaleUp :
	public EventSystem
{
public:
	EventScaleUp();
	~EventScaleUp();
	virtual void run(ImageGO2D* self) override;
};

