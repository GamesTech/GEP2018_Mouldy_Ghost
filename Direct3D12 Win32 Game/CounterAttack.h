#pragma once
#include "Attack.h"

class CounterAttack
	: public Attack
{
public:
	CounterAttack();
	~CounterAttack();

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);
private:
	bool m_relative_damage;
	float m_time_window;
};