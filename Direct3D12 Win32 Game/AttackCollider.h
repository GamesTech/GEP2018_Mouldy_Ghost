#pragma once

#include "GameObject2D.h"

enum Destroy
{
	ON_PLAYER_HIT,
	ON_ANYTHING_HIT,
	AFTER_TIME
};

class AttackCollider
	: public GameObject2D
{
public:
	AttackCollider(Character* _owner, bool _child_to_player,
		float _time, Destroy _contact, int _damage, int _knockback);
	~AttackCollider();

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;

private:
	Character* m_owner;
	Destroy m_destroy;

	float m_despawn_time;

	int m_damage;
	int m_knockback;
};