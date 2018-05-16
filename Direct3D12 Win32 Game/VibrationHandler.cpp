#include "pch.h"
#include "VibrationHandler.h"

void VibrationHandler::onNotify(GameObject2D * entity_, Event event_)
{
	Character* c = static_cast<Character*>(entity_);
	switch (event_)
	{
	case Event::APPLICATION_LOADED:
	{
		for (int i = 0; i < 4; i++)
		{
			setVibration(i, 0, 0, 0);
		}
		break;
	}
	case GAME_OVER:
		for (int i = 0; i < 4; i++)
		{
			setVibration(i, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
		}
		break;
	case PLAYER_HIT:
		setVibration(c->GetControllerIndex(), 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
		break;
	case PLAYER_DEAD:
		setVibration(c->GetControllerIndex(), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
		break;
	case PLAYER_ELIMINATED:
		setVibration(c->GetControllerIndex(), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
		break;
	default:
		break;
	}
}

void VibrationHandler::Tick(DX::StepTimer const & timer)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_vibration_timer[i] > 0)
		{
			m_vibration_timer[i] -= timer.GetElapsedSeconds();
			if (m_vibration_timer[i] <= 0)
			{
				m_game_pads->SetVibration(i, 0, 0);
			}
		}
	}
}

void VibrationHandler::setVibration(int player, float l, float r, float time, float lt, float rt)
{
	m_game_pads->SetVibration(player, l, r, lt, rt);
	m_vibration_timer[player] = time;
}