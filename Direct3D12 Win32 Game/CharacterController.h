#pragma once
#include "pch.h"
#include "InputSystem.h"

/*
Character controller takes the input and transfers them into the
avatar, telling them what actions to perform.
This is a parent class from which PlayerController and AIController will inherit
*/

class Character;

class CharacterController
{
public:
	CharacterController() = default;
	virtual ~CharacterController() = default;

	const int GetControllerID() {return m_controllerID;}

	void SetCharacter(Character* _character);

	virtual GameActions GetInput(GameStateData* _GSD) = 0;

protected:
	int m_controllerID;
	Character* m_character;

	InputSystem m_input;
};