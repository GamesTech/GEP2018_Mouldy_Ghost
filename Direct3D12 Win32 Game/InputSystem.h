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
	CONFIRM,
	QUIT,

	NONE
};

enum GameAction
{
	P_MOVE_LEFT,
	P_MOVE_RIGHT,
	P_CROUCH,
	P_JUMP,
	P_HOLD_UP,

	P_GUARD,
	P_GRAB,
	P_RELEASE_BASIC,
	P_HOLD_BASIC,
	P_RELEASE_SPECIAL,
	P_HOLD_SPECIAL,
	P_PICK_UP,

	P_PAUSE,
	P_QUIT,

#if _DEBUG
	DEBUG_CAM_UP,
	DEBUG_CAM_DOWN,
	DEBUG_CAM_RIGHT,
	DEBUG_CAM_LEFT,
	DEBUG_CAM_IN,
	DEBUG_CAM_OUT,
#endif
};

using GameActions = std::vector<GameAction>;

class GameScene;
class TestScene;

class InputSystem
{
public:
	InputSystem() = default;
	~InputSystem() = default;

	void getAction(int _player, Keyboard::State _state,
		Keyboard::State _prev_state, GameActions& _actions);
	void getAction(GamePad::State _state,
		GamePad::ButtonStateTracker _buttons, GameActions& _actions);

	MenuAction getAction(int _player, Keyboard::State _state,
		Keyboard::State _prev_state);
	MenuAction getAction(GamePad::State _state,
		GamePad::ButtonStateTracker _buttons);

	static bool searchForAction(GameAction _action, GameActions _actions);

private:
};