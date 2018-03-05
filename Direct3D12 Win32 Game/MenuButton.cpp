#include "pch.h"
#include "MenuButton.h"
#include "GameStateData.h"
#include "EventHandler.h"


MenuButton::MenuButton()
{
}

MenuButton::MenuButton(Event _eventToSend)
{
	m_eventToSend = _eventToSend;
	m_highlighted = true;
}


MenuButton::~MenuButton()
{
}

void MenuButton::Tick(GameStateData * _GSD)
{
	if (m_highlighted && 	_GSD->m_gamePadState->IsAPressed())
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(this, m_eventToSend);
		}
	}
}
