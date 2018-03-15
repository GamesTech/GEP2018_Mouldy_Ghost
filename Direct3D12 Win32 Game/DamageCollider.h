#pragma once

#include "GameObject2D.h"
#include "AttackData.h"

#include <vector>

class DamageCollider
	: public ImageGO2D
{
public:
#if _DEBUG
	DamageCollider(DamageColData _data);
#else
	DamageCollider(DamageColData _data);
#endif
	~DamageCollider();

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;

	virtual void Tick(GameStateData* _GSD) override;
private:
	DamageColData m_data;
};