#pragma once

#include "GameObject2D.h"
#include "AttackData.h"

#include <vector>

class SpawnHandler;

class DamageCollider
	: public ImageGO2D
{
public:
	DamageCollider(RenderData * _RD, DamageColData _data, SpawnHandler * _spawner);
	~DamageCollider();

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;

	virtual void Tick(GameStateData* _GSD) override;
	virtual void Render(RenderData* _RD, int _sprite) override;

private:
	DamageColData m_data;
	SpawnHandler* m_spawner;
	float m_lifetime;
};