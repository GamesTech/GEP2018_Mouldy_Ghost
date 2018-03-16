#pragma once
#include <string>
#include "AttackData.h"

class SpawnHandler;
class Attack
{
public:
	Attack() = default;
	~Attack() = default;

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0) = 0;

	const OnHold GetHold() { return m_hold; }
	const float GetDelay() { return m_hold_val; }
protected:
	RenderData* m_RD;
	OnHold m_hold;
	float m_hold_val;	//max charge time for charge attacks, spam rate for repeat attacks
};