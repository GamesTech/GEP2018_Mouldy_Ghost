#pragma once
#include "Attack.h"

enum Effect
{
	E_ABSORB,
	E_REFLECT,
	E_GET_ITEM
};

class PassiveAttack
	: public Attack
{
public:
	PassiveAttack();
	~PassiveAttack();

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);

};