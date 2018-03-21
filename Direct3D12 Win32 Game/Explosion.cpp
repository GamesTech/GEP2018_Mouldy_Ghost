#include "pch.h"
#include "Explosion.h"
#include "GameStateData.h"
#include "VisiblePhysics.h"
#include "SpawnHandler.h"

Explosion::Explosion(Vector2 _pos, RenderData * _RD, 
	GameStateData * _GSD, SpawnHandler * _spawner, 
	float _exp_radius, float _power):ImageGO2D(_RD,"explosion")
{
	m_spawner = _spawner;
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics =Physics2D();
#endif
	m_pos = _pos;
	m_spawner->onNotify(this, Event::OBJECT_INSTANTIATED);

	Rectangle rect = Rectangle(m_pos.x - _exp_radius/2, m_pos.y - _exp_radius / 2,
		m_pos.x + _exp_radius / 2, m_pos.y+ _exp_radius / 2);
	m_physics->SetCollider(rect);

	//m_scale = Vector2(0.1, 0.1);
	
	m_physics->SetGrav(0);

	tag = GameObjectTag::YO;
}

Explosion::~Explosion()
{
}

void Explosion::Tick(GameStateData * _GSD)
{
	elapsed_time += _GSD->m_dt;

	if (elapsed_time > 1)
	{
		m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
	}
}

void Explosion::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLAYER)
	{
		Character* player = static_cast<Character*>(_collision->GetOwner());

		Vector2 dir = player->GetPos() - m_pos;
		dir.Normalize();

		//debug values
		player->Hit(dir, 20, nullptr);
	}
}
