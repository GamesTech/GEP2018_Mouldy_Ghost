#include "pch.h"
#include "CharacterController.h"

void CharacterController::SetCharacter(Character * _character)
{
	m_character = _character;
	_character->getActions()->SetController(this, _character);
}
