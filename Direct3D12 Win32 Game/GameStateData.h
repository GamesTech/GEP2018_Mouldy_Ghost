#pragma once
#include "pch.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

struct GameStateData
{
	Keyboard::State m_keyboardState;
	Keyboard::State m_prevKeyboardState;
	Mouse::State m_mouseState;

	GamePad::State m_gamePadState;
	GamePad::ButtonStateTracker m_buttonState;
	//length of time since last frame
	float m_dt;
};
