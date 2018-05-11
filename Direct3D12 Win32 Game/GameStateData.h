#pragma once
#include "pch.h"
#include "InputSystem.h"
#include "Physics2D.h"
#include "Cursor.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

struct GameStateData
{
	Keyboard::State m_keyboardState;
	Keyboard::State m_prevKeyboardState;
	Mouse::State m_mouseState;
	Mouse::ButtonStateTracker m_mouseButtonState;
	Cursor* m_cursor;

	std::vector<Physics2D*> objects_in_scene;
	std::vector<GameAction> game_actions[4];
	MenuAction menu_action[4];

	Vector2 window_size;

	//length of time since last frame
	float m_dt;
};
