#include "pch.h"

#include "InputSystem.h"

//Keyboard in game controls
void InputSystem::getAction(int _player, Keyboard::State _state, Keyboard::State _prev_state
	, GameActions& _actions)
{
#if _ARCADE
	switch (_player)
	{
	case 1:
	{
		if (_state.D1 && !_prev_state.D1)
		{
			_actions.push_back(P_PAUSE);
		}
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

		if (_state.LeftControl)
		{
			_actions.push_back(P_HOLD_BASIC);
		}
		else if (_prev_state.LeftControl)
		{
			_actions.push_back(P_RELEASE_BASIC);
		}
		if (_state.LeftShift)
		{
			_actions.push_back(P_HOLD_SPECIAL);
		}
		else if (_prev_state.LeftShift)
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
		if (_state.LeftAlt && !_prev_state.LeftAlt)
		{
			_actions.push_back(P_PICK_UP);
		}
		break;
	}
	case 2:
	{
		if (_state.D2 && !_prev_state.D2)
		{
			_actions.push_back(P_PAUSE);
		}
		if (_state.R && !_prev_state.R)
		{
			_actions.push_back(P_JUMP);
		}
		if (_state.D)
		{
			_actions.push_back(P_MOVE_LEFT);
		}
		if (_state.F)
		{
			_actions.push_back(P_CROUCH);
		}
		if (_state.G)
		{
			_actions.push_back(P_MOVE_RIGHT);
		}

		if (_state.A)
		{
			_actions.push_back(P_HOLD_BASIC);
		}
		else if (_prev_state.A)
		{
			_actions.push_back(P_RELEASE_BASIC);
		}
		if (_state.W)
		{
			_actions.push_back(P_HOLD_SPECIAL);
		}
		else if (_prev_state.W)
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
		if (_state.S && !_prev_state.S)
		{
			_actions.push_back(P_PICK_UP);
		}
		break;
	}
}
	if (_state.Escape)
	{
		_actions.push_back(P_QUIT);
	}
#else
	switch (_player)
	{
	case 1:
	{
		if (_state.W)
		{
			if (_prev_state.W)
			{
				_actions.push_back(P_HOLD_UP);
			}
			else
			{
				_actions.push_back(P_JUMP);
			}
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
		if (_state.U && !_prev_state.U)
		{
			_actions.push_back(P_PICK_UP);
		}
		if (_state.Space && !_prev_state.Space)
		{
			_actions.push_back(P_PAUSE);
		}
		break;
	}
	case 2:
	{
		if (_state.Up)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_UP);
#endif
			if (_prev_state.Up)
			{
				_actions.push_back(P_HOLD_UP);
			}
			else
			{
				_actions.push_back(P_JUMP);
			}
		}
		if (_state.Left)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_LEFT);
#endif
			_actions.push_back(P_MOVE_LEFT);
		}
		if (_state.Down)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_DOWN);
#endif
			_actions.push_back(P_CROUCH);
		}
		if (_state.Right)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_RIGHT);
#endif
			_actions.push_back(P_MOVE_RIGHT);
		}

		if (_state.NumPad5)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_OUT);
#endif
			_actions.push_back(P_HOLD_BASIC);
		}
		else if (_prev_state.NumPad5)
		{
			_actions.push_back(P_RELEASE_BASIC);
		}
		if (_state.NumPad1)
		{
#if _DEBUG
			_actions.push_back(DEBUG_CAM_IN);
#endif
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
		if (_state.NumPad6 && !_prev_state.NumPad6)
		{
			_actions.push_back(P_PICK_UP);
		}
		if (_state.Enter && !_prev_state.Enter)
		{
			_actions.push_back(P_PAUSE);
		}
		break;
	}
	}
	if (_state.Escape)
	{
		_actions.push_back(P_QUIT);
	}
#endif
}

//controller in game controls
void InputSystem::getAction(GamePad::State _state,
	GamePad::ButtonStateTracker _buttons, GameActions& _actions)
{
	if (_state.IsAPressed())
	{
#if _DEBUG
		_actions.push_back(DEBUG_CAM_IN);
#endif
		_actions.push_back(P_HOLD_BASIC);
	}
	else if (_buttons.GetLastState().IsAPressed())
	{
		_actions.push_back(P_RELEASE_BASIC);
	}
	if (_state.IsXPressed())
	{
#if _DEBUG
		_actions.push_back(DEBUG_CAM_OUT);
#endif
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

	if (_state.IsYPressed() && !_buttons.GetLastState().IsYPressed())
	{
		_actions.push_back(P_PICK_UP);
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
#if _DEBUG
		_actions.push_back(DEBUG_CAM_LEFT);
#endif
		_actions.push_back(P_MOVE_LEFT);
	}
	if (_state.IsLeftThumbStickRight())
	{
#if _DEBUG
		_actions.push_back(DEBUG_CAM_RIGHT);
#endif
		_actions.push_back(P_MOVE_RIGHT);
	}
	if (_state.IsLeftThumbStickDown())
	{
#if _DEBUG
		_actions.push_back(DEBUG_CAM_DOWN);
#endif
		_actions.push_back(P_CROUCH);
	}
	if (_state.IsLeftThumbStickUp())
	{
#if _DEBUG
		_actions.push_back(DEBUG_CAM_UP);
#endif
		_actions.push_back(P_HOLD_UP);
	}
	if (_state.IsViewPressed())
	{
		_actions.push_back(P_QUIT);
	}
	if (_state.IsMenuPressed() && !_buttons.GetLastState().IsMenuPressed())
	{
		_actions.push_back(P_PAUSE);
	}
}

//keyboard menu controls
MenuAction InputSystem::getAction(int _player, Keyboard::State _state, Keyboard::State _prev_state)
{
#if _ARCADE
	switch (_player)
	{
	case 1:
	{
		if (_state.Up && !_prev_state.Up)
		{
			return NAV_UP;
		}
		if (_state.Left && !_prev_state.Left)
		{
			return NAV_LEFT;
		}
		if (_state.Down && !_prev_state.Down)
		{
			return NAV_DOWN;
		}
		if (_state.Right && !_prev_state.Right)
		{
			return (NAV_RIGHT);
		}
		if (_state.D1 && !_prev_state.D1)
		{
			return (ADVANCE_MENU);
		}
		if (_state.LeftControl && !_prev_state.LeftControl)
		{
			return (CONFIRM);
		}
		if (_state.LeftShift && !_prev_state.LeftShift)
		{
			return PREVIOUS_MENU;
		}
		break;
	}
	case 2:
	{
		if (_state.R && !_prev_state.R)
		{
			return (NAV_UP);
		}
		if (_state.D && !_prev_state.D)
		{
			return (NAV_LEFT);
		}
		if (_state.F && !_prev_state.F)
		{
			return (NAV_DOWN);
		}
		if (_state.G && !_prev_state.G)
		{
			return (NAV_RIGHT);
		}
		if (_state.D2 && !_prev_state.D2)
		{
			return (ADVANCE_MENU);
		}
		if (_state.A && !_prev_state.A)
		{
			return (CONFIRM);
		}
		if (_state.W && !_prev_state.W)
		{
			return PREVIOUS_MENU;
		}
		break;
	}
	default:
		break;
	}
	if (_state.Escape && !_prev_state.Escape)
	{
		return (QUIT);
	}

	return NONE;
#else
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
#endif
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