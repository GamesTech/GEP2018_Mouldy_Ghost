#include "pch.h"
#include "Player.h"
#include "GameStateData.h"

Player::Player(int _controller_id)
{
	m_controllerID = _controller_id;
}

GameActions Player::GetInput(GameStateData * _GSD)
{
	return _GSD->game_actions[m_controllerID];
}