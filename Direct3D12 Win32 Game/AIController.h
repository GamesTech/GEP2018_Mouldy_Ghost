#pragma once

#include "CharacterController.h"

class AIController
	: public CharacterController
{
	enum class AIState
	{
		WAITING,
		FALLING,
		ATTACKING
	};

	enum class Holding
	{
		NONE,
		BASIC,
		SPECIAL
	};

public:
	AIController(int _controller_id);
	~AIController() = default;

	GameActions GetInput(GameStateData* _GSD) override;
private:
	GameActions falling(GameStateData * _GSD);
	GameActions waiting(GameStateData * _GSD);
	GameActions attacking(GameStateData * _GSD);

	float getDist(GameObject2D* object);
	GameActions moveTowards(GameObject2D* _object, GameStateData * _GSD);

	AIState state = AIState::ATTACKING;
	Holding holding = Holding::NONE;
};