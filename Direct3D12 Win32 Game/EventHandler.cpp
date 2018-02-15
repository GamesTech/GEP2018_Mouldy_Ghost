#include "pch.h"
#include "EventHandler.h"
#include "GameStateData.h"

EventHandler* EventHandler::m_event = NULL;

EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}

EventHandler * EventHandler::getInstance()
{
	return m_event;
}

bool EventHandler::playerConfirm(GameStateData * _GSD, int PlayerIndex)
{
	
	if (_GSD->m_buttonState[PlayerIndex].a == DirectX::GamePad::ButtonStateTracker::PRESSED)
	{
		return true;
	}
	return false;
}

bool EventHandler::playerBack(GameStateData * _GSD, int Playerindex)
{
	if (_GSD->m_buttonState[Playerindex].b == GamePad::ButtonStateTracker::PRESSED)
	{
		return true;
	}
	return false;
}

void EventHandler::sendVibration(GamePad * m_gamePad, int playerIndex, float intensity)
{
	m_gamePad->SetVibration(playerIndex, intensity, intensity);
}


