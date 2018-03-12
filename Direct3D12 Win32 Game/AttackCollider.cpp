#include "pch.h"
#include "AttackCollider.h"

AttackCollider::AttackCollider(Character * _owner, bool _child_to_player, float _time, Destroy _contact, int _damage, int _knockback)
{
	tag = GameObjectTag::ATTACK;
	m_owner = _owner;
	if (_child_to_player)
	{
		parent = _owner;
	}
	m_despawn_time = _time;
	m_destroy = _contact;

	m_damage = _damage;
	m_knockback = _knockback;
}

AttackCollider::~AttackCollider()
{
}

void AttackCollider::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (_collision->GetOwner() != m_owner)
	{
		GameObjectTag collision_tag = _collision->GetOwner()->GetTag();
		if (collision_tag == GameObjectTag::PLAYER)
		{
			//do damage
			_collision->AddForce(_normal * m_knockback);
		}
	}
}