#include "pch.h"
#include "GameSettingsHandler.h"


GameSettingsHandler::GameSettingsHandler()
{
}


GameSettingsHandler::~GameSettingsHandler()
{
}

void GameSettingsHandler::onNotify(GameObject2D * entity_, Event event_)
{
	switch (event_)
	{
	case Event::GAME_SETTINGS_INCREASE_LIVES:
		m_lives++;
		break;
	case Event::GAME_SETTINGS_DECREASE_LIVES:
		m_lives--;
		break;
	case Event::GAME_SETTINGS_INCREASE_TIME:
		m_time += 10;
		break;
	case Event::GAME_SETTINGS_DECREASE_TIME:
		m_time -= 10;
		break;
	default:
			break;
	}
}
