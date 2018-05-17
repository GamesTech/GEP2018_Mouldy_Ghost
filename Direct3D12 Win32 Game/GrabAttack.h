#pragma once
#include "Attack.h"

class GrabAttack
	: public Attack
{
public:
	GrabAttack();
	~GrabAttack();

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);
};