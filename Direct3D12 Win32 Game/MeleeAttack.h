#pragma once
#include "Attack.h"
#include "DamageCollider.h"

class MeleeAttack
	:public Attack
{
public:
	MeleeAttack(std::string _attack_file);
	~MeleeAttack() = default;
	virtual void PerformAttack(int _facing);

private:
	DamageCollider* m_collider;
	DamageColData m_data;
};