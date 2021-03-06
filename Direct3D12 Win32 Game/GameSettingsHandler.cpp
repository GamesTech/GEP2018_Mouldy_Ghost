#include "pch.h"
#include "GameSettingsHandler.h"


GameSettingsHandler::GameSettingsHandler()
{
#if _DEBUG
	m_lives = 1;
#else
	m_lives = 3;
#endif
	m_time = 60;
	m_infiniteTime = false;
	m_infiniteLives = false;

	
}


GameSettingsHandler::~GameSettingsHandler()
{
}

void GameSettingsHandler::onNotify(GameObject2D * entity_, Event event_)
{
	switch (event_)
	{
	case Event::GAME_SETTINGS_INCREASE_LIVES:
		if (m_lives <= 20)
		{
			m_lives++;
		}
		else
		{
			m_lives = 1;
		}

		if (m_lives > 20)
		{
			m_infiniteLives = true;
		}
		else if (m_lives > 0)
		{
			m_infiniteLives = false;
		}
		break;
	case Event::GAME_SETTINGS_DECREASE_LIVES:
		if (m_lives >= 1)
		{
			m_lives--;
		}

		if (m_lives < 1)
		{
			m_infiniteLives = true;
			m_lives = 21;
		}
		else if (m_lives <= 20)
		{
			m_infiniteLives = false;
		}
		break;
	case Event::GAME_SETTINGS_INCREASE_TIME:
		if (m_time < 3630)
		{
			m_time += 30;
		}
		else
		{
			m_time = 30;
		}

		if (m_time >= 3630)
		{
			m_infiniteTime = true;
		}
		else if (m_time > 0)
		{
			m_infiniteTime = false;
		}
		break;
	case Event::GAME_SETTINGS_DECREASE_TIME:
		if (m_time > 0)
		{
			m_time -= 30;
		}

		if (m_time <= 0)
		{
			m_infiniteTime = true;
			m_time = 3630;
		}
		else if (m_time < 3630)
		{
			m_infiniteTime = false;
		}
		break;
	default:
			break;
	}
}

void GameSettingsHandler::onNotify(int _item_index, Event event_)
{
	if (event_ == Event::GAME_SETTINGS_ITEM_ACTIVATION)
	{
		available_items[_item_index] = !available_items[_item_index];
	}
	else if (event_ == Event::GAME_SETTING_STAGE_SELECT)
	{
		m_stage_selected = _item_index;
		m_is_stage_selected = true;
	}

}

int GameSettingsHandler::getLives()
{
	return m_lives;
}

float GameSettingsHandler::getTime()
{
	return m_time;
}

bool GameSettingsHandler::getInfiniteTime()
{
	return m_infiniteTime;
}

bool GameSettingsHandler::getInfiniteLives()
{
	return m_infiniteLives;
}

void GameSettingsHandler::addAvailableItemSlot()
{
	available_items.push_back(true);
}
