#include "pch.h"
#include "DamageCollider.h"
#include "Physics2D.h"
#include "SpawnHandler.h"

DamageCollider::DamageCollider(RenderData* _RD, DamageColData _data, SpawnHandler* _spawner) : ImageGO2D(_RD, "hit")
{
	m_spawner = _spawner;
	m_physics = new Physics2D();
	m_spawner->onNotify(this, Event::OBJECT_INSTANTIATED);

	Rectangle rect = Rectangle(m_pos.x, m_pos.y, 10, 10);
	m_physics->SetCollider(rect);

	m_physics->SetOwner(this);
	m_physics->SetGrav(0);
	tag = GameObjectTag::ATTACK;
	m_data = _data;
	if (_data.child_to_player)
	{
		parent = m_data.user;
	}
	m_lifetime = 0;
}

DamageCollider::~DamageCollider()
{
	delete m_physics;
	m_physics = nullptr;
}

void DamageCollider::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (_collision->GetOwner() != m_data.user)
	{
		GameObjectTag collision_tag = _collision->GetOwner()->GetTag();
		if (collision_tag == GameObjectTag::PLAYER)
		{
			Character* target = static_cast<Character*>(_collision->GetOwner());
			target->TakeDamage(m_data.damage);
			target->GetHit(_normal, -m_data.knockback * 500);

			if (m_data.contact == Destroy::ON_PLAYER_HIT)
			{
				m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
			}
		}
		if (m_data.contact == Destroy::ON_ANYTHING_HIT)
		{
			m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
		}
	}
}

void DamageCollider::Tick(GameStateData * _GSD)
{
	m_physics->AddForce(m_data.direction * m_data.speed * 10);
	m_physics->Tick(_GSD, m_pos);

	m_lifetime += _GSD->m_dt;
	if (m_lifetime > m_data.time)
	{
		m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
	}
}