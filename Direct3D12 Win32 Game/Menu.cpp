#include "pch.h"
#include "Menu.h"
#include "GameStateData.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

Menu::Menu(Vector2 _pos, MenuButton _first, std::string _firstButtonText)
{
	_first.setText(_firstButtonText);
	m_buttons.push_back(_first);
	SetPos(_pos);
	m_nextButtonPos = GetPos();
	m_distanceBetweenButtons = 100;
	m_buttons[0].SetPos(m_nextButtonPos);
	m_nextButtonPos.y += m_distanceBetweenButtons;

	m_highlighted_index = 0;
	m_buttons[m_highlighted_index].setHighlighted(true);
	
}

void Menu::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos)
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].Render(_RD, _sprite);
	}
}

void Menu::Tick(GameStateData * _GSD)
{
	if (_GSD->menu_action[0] == MenuAction::NAV_DOWN)
	{
		m_buttons[m_highlighted_index].setHighlighted(false);
		m_highlighted_index++;
		if (m_highlighted_index >= m_buttons.size())
		{
			m_highlighted_index = 0;
		}

		m_buttons[m_highlighted_index].setHighlighted(true);
	}

	if (_GSD->menu_action[0] == MenuAction::NAV_UP)
	{
		m_buttons[m_highlighted_index].setHighlighted(false);
		m_highlighted_index--;
		if (m_highlighted_index < 0)
		{
			m_highlighted_index = m_buttons.size() - 1;
		}

		m_buttons[m_highlighted_index].setHighlighted(true);
	}

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].Tick(_GSD);
	}
}

void Menu::addButton(MenuButton _buttonToAdd, std::string _buttonText)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		_buttonToAdd.addListener(listeners[i]);
	}
	_buttonToAdd.setText(_buttonText);
	_buttonToAdd.SetPos(m_nextButtonPos);
	m_nextButtonPos.y += m_distanceBetweenButtons;
	m_buttons.push_back(_buttonToAdd);
}

void Menu::init()
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		for (int j = 0; j < listeners.size(); j++)
		{
			m_buttons[i].addListener(listeners[j]);
		}
	}
}
