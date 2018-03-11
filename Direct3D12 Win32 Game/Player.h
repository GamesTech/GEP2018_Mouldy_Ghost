#pragma once
#include "CharacterController.h"

class Player
	: public CharacterController
{
public:
	Player(int _controller_id);
	~Player() = default;

	virtual GameActions GetInput(GameStateData* _GSD);
};