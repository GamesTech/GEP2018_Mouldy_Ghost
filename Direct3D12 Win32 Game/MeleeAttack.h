#pragma once
#include "Attack.h"
#include "DamageCollider.h"

class SpawnHandler;

class MeleeAttack
	:public Attack
{
public:
	MeleeAttack(std::string _attack_file);
	~MeleeAttack() = default;
	virtual void PerformAttack(Vector2 _position, int _facing,
		Character* _user, GameStateData* _GSD, SpawnHandler* _spawner);
private:
	DamageCollider* m_collider;
	DamageColData m_data;
};