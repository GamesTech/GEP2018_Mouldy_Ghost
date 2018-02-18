#pragma once
#include "pch.h"
#include "Physics2D.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

struct GameStateData
{
	std::vector<Physics2D*> objects_in_scene;

	Keyboard::State m_keyboardState;
	Keyboard::State m_prevKeyboardState;
	Mouse::State m_mouseState;

	GamePad::State m_gamePadState[4];
	GamePad::ButtonStateTracker m_buttonState[4];

	//length of time since last frame
	float m_dt;
};
