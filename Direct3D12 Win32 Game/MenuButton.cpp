#include "pch.h"
#include "MenuButton.h"
#include "GameStateData.h"
#include "EventHandler.h"


MenuButton::MenuButton()

{}

MenuButton::MenuButton(Event _eventToSend, RenderData * _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	m_physics = new Physics2D();
	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
	m_eventToSend = _eventToSend;
	m_highlighted = true;
}


MenuButton::~MenuButton()
{
}

void MenuButton::Tick(GameStateData * _GSD)
{
	if (_GSD->game_actions[0].size() > 0)
	{
		if (m_highlighted && 	_GSD->game_actions[0][0] == GameAction::P_HOLD_BASIC)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, m_eventToSend);
			}
		}
	}
}
