#include "pch.h"
#include "MenuButton.h"
#include "GameStateData.h"
#include "EventHandler.h"
#include "GameSettingsHandler.h"


MenuButton::MenuButton()
{
}

MenuButton::MenuButton(Event _eventToSend, RenderData * _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	//constructor for a single event (press a to do the thing)
	type = ButtonType::SINGLE_EVENT;
	m_physics = std::make_shared<Physics2D>();
	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
	m_eventToSend = _eventToSend;
	m_highlighted = false;
	m_text.SetText("I am test button text");
	m_text.SetColour(Color(0, 0, 0));
}

MenuButton::MenuButton(Event _leftEventToSend, Event _rightEventToSend, RenderData * _RD, string _filename) : ImageGO2D (_RD, _filename)
{
	//constructor for a two event button (left/right for increasing of decreasing a value)
	type = ButtonType::TWO_EVENT;
	m_physics = std::make_shared<Physics2D>();
	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
	m_eventLeft = _leftEventToSend;
	m_eventRight = _rightEventToSend;
	m_highlighted = false;
	m_text.SetText("I am a two event button");
	m_text.SetColour(Color(0, 0, 0));
}


MenuButton::~MenuButton()
{
}

void MenuButton::Tick(GameStateData * _GSD)
{
	if (m_highlighted)
	{
		SetColour(Color(Colors::AliceBlue));
	}
	else
	{
		SetColour(Color(1, 1, 1, 0));
	}

	for (int controller = 0; controller < 4; controller++)
	{
		//take input from all controllers
		switch (type)
		{
		case ButtonType::SINGLE_EVENT:
			if (_GSD->menu_action[controller] == MenuAction::CONFIRM && m_highlighted)
			{
				//if the button is highlighted and they press A then do the thing
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(this, Event::BUTTON_PRESSED);
					listeners[i]->onNotify(this, m_eventToSend);

					if (listeners[i]->getType() == "GameSettings"
						&& m_eventToSend == Event::GAME_SETTINGS_ITEM_ACTIVATION)
					{
						GameSettingsHandler* tmp = static_cast<GameSettingsHandler*>(listeners[i]);

						tmp->onNotify(m_index_to_send, m_eventToSend);
					}

				}

				
			}
			break;
		case ButtonType::TWO_EVENT:
			if (_GSD->menu_action[controller] == MenuAction::NAV_LEFT && m_highlighted)
			{
				//if the button is highlighted and they press left or right then do the thing
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(this, m_eventLeft);
				}
			}
			if (_GSD->menu_action[controller] == MenuAction::NAV_RIGHT && m_highlighted)
			{
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(this, m_eventRight);
				}
			}
			break;
		}
	}
	//set the position of the text in accordance with the position of the button
	m_text.SetPos(this->GetPos() + m_textOffset + Vector2(60,-10));
}

void MenuButton::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	ImageGO2D::Render(_RD, _sprite);
	m_text.Render(_RD, _sprite);
}

void MenuButton::setText(std::string _text)
{
	m_text.SetText(_text);
}

Event MenuButton::getTopEvent()
{
	if (m_eventLeft != NULL)
	{
		return m_eventLeft;
	}
	else
	{
		return m_eventToSend;
	}
}

void MenuButton::setHighlighted(bool _highlighted)
{
	m_highlighted = _highlighted;
}