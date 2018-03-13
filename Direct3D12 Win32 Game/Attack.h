#pragma once
#include <string>
#include "AttackData.h"

class Attack
{
public:
	Attack() = default;
	~Attack() = default;

	virtual void PerformAttack(int _facing, GameStateData* _GSD) = 0;
private:
	OnHold _hold;
};