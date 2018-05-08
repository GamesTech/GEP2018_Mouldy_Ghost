#include "pch.h"
#include "HumanController.h"
#include "GameStateData.h"

HumanController::HumanController(int _controller_id)
{
	m_controllerID = _controller_id;
}

GameActions HumanController::GetInput(GameStateData * _GSD)
{
	return _GSD->game_actions[m_controllerID];
}