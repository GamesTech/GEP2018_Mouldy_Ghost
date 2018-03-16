#pragma once

#include "Attack.h"
#include "DamageCollider.h"

class DashAttack
	: public MeleeAttack
{
public:
	DashAttack(std::string _attack_file, RenderData* _RD);
	~DashAttack() = default;

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);

private:
	Vector2 m_dash_direction;
	float m_dash_distance;
	int m_num_hits;
};