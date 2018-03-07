#pragma once
#include "pch.h"
#include "InputSystem.h"
#include "Physics2D.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

struct GameStateData
{
	std::vector<Physics2D*> objects_in_scene;
	std::vector<GameAction> game_actions;
	MenuAction menu_action;

	//length of time since last frame
	float m_dt;
};
