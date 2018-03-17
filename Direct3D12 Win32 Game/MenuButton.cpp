#include "pch.h"
#include "MenuButton.h"
#include "GameStateData.h"
#include "EventHandler.h"


MenuButton::MenuButton()

{}

MenuButton::MenuButton(Event _eventToSend, RenderData * _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	type = ButtonType::SINGLE_EVENT;
	m_physics = new Physics2D();
	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
	m_eventToSend = _eventToSend;
	m_highlighted = false;
	m_text.SetText("I am test button text");
}

MenuButton::MenuButton(Event _leftEventToSend, Event _rightEventToSend, RenderData * _RD, string _filename) : ImageGO2D (_RD, _filename)
{
	type = ButtonType::TWO_EVENT;
	m_physics = new Physics2D();
	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
	m_eventLeft = _leftEventToSend;
	m_eventRight = _rightEventToSend;
	m_highlighted = false;
	m_text.SetText("I am a two event button");
}


MenuButton::~MenuButton()
{
}

void MenuButton::Tick(GameStateData * _GSD)
{
	if (m_highlighted)
	{
		scaleFromPoint(GetPos(), Vector2(1.1f, 1.1f));
		SetColour(Color(Colors::AliceBlue));
	}
	else
	{
		scaleFromPoint(GetPos(), Vector2(1.0f, 1.0f));
	}

	switch (type)
	{
	case ButtonType::SINGLE_EVENT:
		if (_GSD->menu_action[0] == MenuAction::CONFIRM && m_highlighted)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, m_eventToSend);
			}
		}
		break;
	case ButtonType::TWO_EVENT:
		if (_GSD->menu_action[0] == MenuAction::NAV_LEFT && m_highlighted)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, m_eventLeft);
			}
		}
		if (_GSD->menu_action[0] == MenuAction::NAV_RIGHT && m_highlighted)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, m_eventRight);
			}
		}
		break;
	}
	m_text.SetPos(this->GetPos() + m_textOffset);
}

void MenuButton::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos)
{
	ImageGO2D::Render(_RD, _sprite);
	m_text.Render(_RD, _sprite);
}

void MenuButton::setText(std::string _text)
{
	m_text.SetText(_text);
}

void MenuButton::setHighlighted(bool _highlighted)
{
	m_highlighted = _highlighted;
}
