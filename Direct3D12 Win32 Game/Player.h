#pragma once
#include "CharacterController.h"

class Player
	: public CharacterController
{
public:
	Player(int _controller_id);
	~Player() = default;

    //get the input assigned to that controller id
	virtual GameActions GetInput(GameStateData* _GSD);
};