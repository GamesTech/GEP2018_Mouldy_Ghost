#include "pch.h"
#include "DamageCollider.h"
#include "Physics2D.h"
#include "SpawnHandler.h"

DamageCollider::DamageCollider(RenderData* _RD, DamageColData _data, SpawnHandler* _spawner) : ImageGO2D(_RD, _data.file)
{
	m_spawner = _spawner;
	m_physics = std::make_shared<Physics2D>();

	m_scale.x = _data.size.x / m_spriteSize.x;
	m_scale.y = _data.size.y / m_spriteSize.y;

	Rectangle rect = Rectangle(m_pos.x, m_pos.y, _data.size.x, _data.size.y);
	m_physics->SetCollider(rect);

	m_physics->SetOwner(this);
	if (_data.grav)
	{
		m_physics->SetGrav(1);
	}
	else
	{
		m_physics->SetGrav(0);
	}
	tag = GameObjectTag::ATTACK;
	m_data = _data;
	if (_data.child_to_player)
	{
		m_data.user->AddChild(this);
		parent = m_data.user;
	}
	m_lifetime = 0;
}

DamageCollider::~DamageCollider()
{
	if(parent)
	parent->RemoveChild(this);
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
			target->Hit(_normal, -m_data.knockback * 500, m_data.user);

			if (m_data.contact == Destroy::ON_PLAYER_HIT)
			{
				m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
				return;
			}
		}
		if (m_data.contact == Destroy::ON_ANYTHING_HIT)
		{
			m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
			return;
		}
	}
}

void DamageCollider::Tick(GameStateData * _GSD)
{
	calculateRotation();

	if (m_data.grav)
	{
		m_physics->AddForce(Vector2(0, 10));
	}

	m_physics->AddForce(m_data.direction * m_data.speed * 10);
	m_physics->Tick(_GSD, m_pos);

	m_lifetime += _GSD->m_dt;

	m_colour.A(m_lifetime * 2);

	if (m_lifetime > m_data.time)
	{
		m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
		return;
	}
}

void DamageCollider::calculateRotation()
{
	Vector2 absolute_direction = m_data.direction * m_data.speed;
	absolute_direction.Normalize();
	if (absolute_direction.x < 0)
	{
		flipped = true;
	}
}