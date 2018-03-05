#pragma once
#include "ImageGO2D.h"
#include "Events.h"
class MenuButton :
	public ImageGO2D
{
public:
	MenuButton();
	MenuButton(Event _eventToSend);
	~MenuButton();
	virtual void Tick(GameStateData* _GSD) override;
private:
	Event m_eventToSend;
	bool m_highlighted;
};

