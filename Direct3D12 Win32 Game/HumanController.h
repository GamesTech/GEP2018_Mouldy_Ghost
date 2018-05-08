#pragma once
#include "CharacterController.h"

class HumanController
	: public CharacterController
{
public:
	HumanController(int _controller_id);
	~HumanController() = default;

	virtual GameActions GetInput(GameStateData* _GSD);
};