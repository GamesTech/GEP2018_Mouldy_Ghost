#include "pch.h"

#include "InputSystem.h"
#include "GameScene.h"
#include "TestScene.h"

//TODO: All instances of "testscene" should be replaced with menuscene when it exists

//Keyboard in game controls
GameActions InputSystem::getAction(Keyboard::State _state, Keyboard::State _prev_state, GameScene * _scene)
{
	GameActions ret_actions;
	if (_state.W && !_prev_state.W)
	{
		ret_actions.push_back(P_JUMP);
	}
	if (_state.A)
	{
		ret_actions.push_back(P_MOVE_LEFT);
	}
	if (_state.S)
	{
		ret_actions.push_back(P_CROUCH);
	}
	if (_state.D)
	{
		ret_actions.push_back(P_MOVE_RIGHT);
	}

	if (_state.Y)
	{
		ret_actions.push_back(P_HOLD_BASIC);
	}
	else if (_prev_state.Y)
	{
		ret_actions.push_back(P_RELEASE_BASIC);
	}
	if (_state.U)
	{
		ret_actions.push_back(P_HOLD_SPECIAL);
	}
	else if (_prev_state.U)
	{
		ret_actions.push_back(P_RELEASE_SPECIAL);
	}

	if (_state.H && !_prev_state.H)
	{
		ret_actions.push_back(P_GRAB);
	}
	if (_state.J && !_prev_state.J)
	{
		ret_actions.push_back(P_GUARD);
	}

	return ret_actions;
}

GameActions InputSystem::getAction(GamePad::State _state, GamePad::ButtonStateTracker _buttons, GameScene * _scene)
{
	GameActions ret_actions;

	if (_state.IsAPressed())
	{
		ret_actions.push_back(P_HOLD_BASIC);
	}
	else if (_buttons.GetLastState().IsAPressed())
	{
		ret_actions.push_back(P_RELEASE_BASIC);
	}
	if (_state.IsXPressed())
	{
		ret_actions.push_back(P_HOLD_SPECIAL);
	}
	else if (_buttons.GetLastState().IsXPressed())
	{
		ret_actions.push_back(P_RELEASE_SPECIAL);
	}

	if (_state.IsBPressed() && !_buttons.GetLastState().IsBPressed())
	{
		ret_actions.push_back(P_JUMP);
	}

	if (_state.IsRightTriggerPressed())
	{
		ret_actions.push_back(P_GUARD);
	}
	if (_state.IsRightShoulderPressed() && !_buttons.GetLastState().IsRightShoulderPressed())
	{
		ret_actions.push_back(P_GRAB);
	}

	if (_state.IsLeftThumbStickLeft())
	{
		ret_actions.push_back(P_MOVE_LEFT);
	}
	if (_state.IsLeftThumbStickRight())
	{
		ret_actions.push_back(P_MOVE_RIGHT);
	}
	if (_state.IsLeftThumbStickDown())
	{
		ret_actions.push_back(P_CROUCH);
	}

	return ret_actions;
}

MenuAction InputSystem::getAction(Keyboard::State _state, Keyboard::State _prev_state, TestScene * _scene)
{
	if (_state.W && !_prev_state.W)
	{
		return (NAV_UP);
	}
	if (_state.A && !_prev_state.A)
	{
		return (NAV_LEFT);
	}
	if (_state.S && !_prev_state.S)
	{
		return (NAV_DOWN);
	}
	if (_state.D && !_prev_state.D)
	{
		return (NAV_LEFT);
	}

	if (_state.Enter && !_prev_state.Enter)
	{
		return (ADVANCE_MENU);
	}
	if (_state.Escape && !_prev_state.Escape)
	{
		return (PREVIOUS_MENU);
	}

	return NONE;
}

MenuAction InputSystem::getAction(GamePad::State _state, GamePad::ButtonStateTracker _buttons, TestScene * _scene)
{
	if (_state.IsAPressed() && !_buttons.GetLastState().IsAPressed())
	{
		return ADVANCE_MENU;
	}

	if (_state.IsBPressed() && !_buttons.GetLastState().IsBPressed())
	{
		return PREVIOUS_MENU;
	}


	if (_state.IsLeftThumbStickLeft() &&
		!_buttons.GetLastState().IsLeftThumbStickLeft())
	{
		return NAV_LEFT;
	}
	if (_state.IsLeftThumbStickRight() &&
		!_buttons.GetLastState().IsLeftThumbStickRight())
	{
		return NAV_RIGHT;
	}
	if (_state.IsLeftThumbStickUp() &&
		!_buttons.GetLastState().IsLeftThumbStickUp())
	{
		return NAV_UP;
	}
	if (_state.IsLeftThumbStickDown() &&
		!_buttons.GetLastState().IsLeftThumbStickDown())
	{
		return NAV_DOWN;
	}

	return NONE;
}