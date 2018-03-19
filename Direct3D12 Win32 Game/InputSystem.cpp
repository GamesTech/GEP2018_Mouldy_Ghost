#include "pch.h"

#include "InputSystem.h"

//Keyboard in game controls
void InputSystem::getAction(int _player, Keyboard::State _state, Keyboard::State _prev_state
	, GameActions& _actions)
{
	switch (_player)
	{
	case 1:
	{
		if (_state.W && !_prev_state.W)
		{
			_actions.push_back(P_JUMP);
		}
		if (_state.A)
		{
			_actions.push_back(P_MOVE_LEFT);
		}
		if (_state.S)
		{
			_actions.push_back(P_CROUCH);
		}
		if (_state.D)
		{
			_actions.push_back(P_MOVE_RIGHT);
		}

		if (_state.Y)
		{
			_actions.push_back(P_HOLD_BASIC);
		}
		else if (_prev_state.Y)
		{
			_actions.push_back(P_RELEASE_BASIC);
		}
		if (_state.G)
		{
			_actions.push_back(P_HOLD_SPECIAL);
		}
		else if (_prev_state.G)
		{
			_actions.push_back(P_RELEASE_SPECIAL);
		}

		if (_state.H && !_prev_state.H)
		{
			_actions.push_back(P_GRAB);
		}
		if (_state.J && !_prev_state.J)
		{
			_actions.push_back(P_GUARD);
		}
		break;
	}
	case 2:
	{
		if (_state.Up && !_prev_state.Up)
		{
			_actions.push_back(P_JUMP);
		}
		if (_state.Left)
		{
			_actions.push_back(P_MOVE_LEFT);
		}
		if (_state.Down)
		{
			_actions.push_back(P_CROUCH);
		}
		if (_state.Right)
		{
			_actions.push_back(P_MOVE_RIGHT);
		}

		if (_state.NumPad5)
		{
			_actions.push_back(P_HOLD_BASIC);
		}
		else if (_prev_state.NumPad5)
		{
			_actions.push_back(P_RELEASE_BASIC);
		}
		if (_state.NumPad1)
		{
			_actions.push_back(P_HOLD_SPECIAL);
		}
		else if (_prev_state.NumPad1)
		{
			_actions.push_back(P_RELEASE_SPECIAL);
		}

		if (_state.NumPad2 && !_prev_state.NumPad2)
		{
			_actions.push_back(P_GRAB);
		}
		if (_state.NumPad3 && !_prev_state.NumPad3)
		{
			_actions.push_back(P_GUARD);
		}
		break;
	}
	}
	if (_state.Escape)
	{
		_actions.push_back(P_QUIT);
	}
}

//controller in game controls
void InputSystem::getAction(GamePad::State _state,
	GamePad::ButtonStateTracker _buttons, GameActions& _actions)
{
	if (_state.IsAPressed())
	{
		_actions.push_back(P_HOLD_BASIC);
	}
	else if (_buttons.GetLastState().IsAPressed())
	{
		_actions.push_back(P_RELEASE_BASIC);
	}
	if (_state.IsXPressed())
	{
		_actions.push_back(P_HOLD_SPECIAL);
	}
	else if (_buttons.GetLastState().IsXPressed())
	{
		_actions.push_back(P_RELEASE_SPECIAL);
	}

	if (_state.IsBPressed() && !_buttons.GetLastState().IsBPressed())
	{
		_actions.push_back(P_JUMP);
	}

	if (_state.IsRightTriggerPressed())
	{
		_actions.push_back(P_GUARD);
	}
	if (_state.IsRightShoulderPressed() && !_buttons.GetLastState().IsRightShoulderPressed())
	{
		_actions.push_back(P_GRAB);
	}

	if (_state.IsLeftThumbStickLeft())
	{
		_actions.push_back(P_MOVE_LEFT);
	}
	if (_state.IsLeftThumbStickRight())
	{
		_actions.push_back(P_MOVE_RIGHT);
	}
	if (_state.IsLeftThumbStickDown())
	{
		_actions.push_back(P_CROUCH);
	}
	if (_state.IsLeftThumbStickUp())
	{
		_actions.push_back(P_HOLD_UP);
	}
	if (_state.IsViewPressed())
	{
		_actions.push_back(P_QUIT);
	}
}

//keyboard menu controls
MenuAction InputSystem::getAction(int _player, Keyboard::State _state, Keyboard::State _prev_state)
{
	switch (_player)
	{
	case 1:
	{
		if (_state.W && !_prev_state.W)
		{
			return NAV_UP;
		}
		if (_state.A && !_prev_state.A)
		{
			return NAV_LEFT;
		}
		if (_state.S && !_prev_state.S)
		{
			return NAV_DOWN;
		}
		if (_state.D && !_prev_state.D)
		{
			return (NAV_RIGHT);
		}

		if (_state.R && !_prev_state.R)
		{
			return (CONFIRM);
		}
		if (_state.Y && !_prev_state.Y)
		{
			return PREVIOUS_MENU;
		}
		break;
	}
	case 2:
	{
		if (_state.Up && !_prev_state.Up)
		{
			return (NAV_UP);
		}
		if (_state.Left && !_prev_state.Left)
		{
			return (NAV_LEFT);
		}
		if (_state.Down && !_prev_state.Down)
		{
			return (NAV_DOWN);
		}
		if (_state.Right && !_prev_state.Right)
		{
			return (NAV_RIGHT);
		}

		if (_state.NumPad1 && !_prev_state.NumPad1)
		{
			return (CONFIRM);
		}
		if (_state.NumPad3 && !_prev_state.NumPad3)
		{
			return PREVIOUS_MENU;
		}
		break;
	}
	default:
		break;
	}
	if (_state.Enter && !_prev_state.Enter)
	{
		return ADVANCE_MENU;
	}
	if (_state.Escape && !_prev_state.Escape)
	{
		return (QUIT);
	}

	return NONE;
}

//controller menu controls
MenuAction InputSystem::getAction(GamePad::State _state, GamePad::ButtonStateTracker _buttons)
{
	if (_state.IsStartPressed() && !_buttons.GetLastState().IsStartPressed())
	{
		return ADVANCE_MENU;
	}

	if (_state.IsBackPressed() && !_buttons.GetLastState().IsBackPressed())
	{
		return PREVIOUS_MENU;
	}

	if (_state.IsAPressed() && !_buttons.GetLastState().IsAPressed())
	{
		return CONFIRM;
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

bool InputSystem::searchForAction(GameAction _action, GameActions _actions)
{
	for (int i = 0; i < _actions.size(); i++)
	{
		if (_actions[i] == _action)
		{
			return true;
		}
	}
	return false;
}