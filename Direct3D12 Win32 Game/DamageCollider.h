#pragma once

#include "GameObject2D.h"
#include "AttackData.h"

class DamageCollider
	: public ImageGO2D
{
public:
	DamageCollider(DamageColData _data);
	~DamageCollider();

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;
private:
	DamageColData m_data;
};