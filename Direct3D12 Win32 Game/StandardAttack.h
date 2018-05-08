#pragma once
#include "Attack.h"
#include "DamageCollider.h"

class SpawnHandler;

class StandardAttack
	:public Attack
{
public:
	StandardAttack() = default;
	StandardAttack(std::string _attack_file, RenderData* _RD);
	~StandardAttack() = default;

	virtual void PerformAttack(Vector2 _position, int _direction,
		Character* _user, GameStateData* _GSD,
		SpawnHandler* _spawner, float _charge = 0);
protected:
	DamageColData m_data;
};