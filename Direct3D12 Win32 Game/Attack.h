#pragma once
#include <string>
#include "AttackData.h"

class SpawnHandler;
class Attack
{
public:
	Attack() = default;
	~Attack() = default;

	virtual void PerformAttack(Vector2 _position, int _facing,
		Character* _user, GameStateData* _GSD, SpawnHandler* _spawner) = 0;
private:
	OnHold _hold;
};