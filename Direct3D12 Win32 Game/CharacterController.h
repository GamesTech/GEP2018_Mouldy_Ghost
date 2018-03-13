#pragma once
#include "pch.h"
#include "InputSystem.h"

class Character;

class CharacterController
{
public:
	CharacterController() = default;
	virtual ~CharacterController() = default;

	void SetControllerID(int _ID){m_controllerID = _ID;}
	const int GetControllerID() {return m_controllerID;}

	void SetCharacter(Character* _character);

	virtual GameActions GetInput(GameStateData* _GSD) = 0;

protected:
	int m_controllerID;
	Character* m_character;

	InputSystem m_input;
};