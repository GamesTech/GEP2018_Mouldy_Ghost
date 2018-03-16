#pragma once
#include "Attack.h"
#include "DamageCollider.h"

class SpawnHandler;

class MeleeAttack
	:public Attack
{
public:
	MeleeAttack(std::string _attack_file, RenderData* _RD);
	~MeleeAttack() = default;
	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);
private:
	DamageColData m_data;
};