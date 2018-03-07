#pragma once

#include "pch.h"

enum MenuAction
{
	NAV_UP,
	NAV_DOWN,
	NAV_LEFT,
	NAV_RIGHT,
	ADVANCE_MENU,
	PREVIOUS_MENU,

	NONE
};

enum GameAction
{
	P_MOVE_LEFT,
	P_MOVE_RIGHT,
	P_CROUCH,
	P_JUMP,

	P_GUARD,
	P_GRAB,
	P_RELEASE_BASIC,
	P_HOLD_BASIC,
	P_RELEASE_SPECIAL,
	P_HOLD_SPECIAL
};

using GameActions = std::vector<GameAction>;

class GameScene;
class TestScene;

class InputSystem
{
public:
	InputSystem() = default;
	~InputSystem() = default;

	GameActions getAction(Keyboard::State _state,
		Keyboard::State _prev_state, GameScene* _scene);
	GameActions getAction(GamePad::State _state,
		GamePad::ButtonStateTracker _buttons, GameScene* _scene);

	MenuAction getAction(Keyboard::State _state,
		Keyboard::State _prev_state, TestScene* _scene);
	MenuAction getAction(GamePad::State _state,
		GamePad::ButtonStateTracker _buttons, TestScene* _scene);
};