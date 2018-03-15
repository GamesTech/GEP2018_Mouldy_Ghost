#pragma once

#include "GameObject2D.h"
#include "AttackData.h"

#include <vector>

class SpawnHandler;

class DamageCollider
	: public ImageGO2D
{
public:
	DamageCollider(DamageColData _data, SpawnHandler* _spawner);
	~DamageCollider();

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;

	virtual void Tick(GameStateData* _GSD) override;
private:
	DamageColData m_data;
	SpawnHandler* m_spawner;
};