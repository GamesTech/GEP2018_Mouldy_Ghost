#include "pch.h"
#include "Explosive.h"
#include "GameStateData.h"
#include "Explosion.h"

Explosive::Explosive()
{
}

Explosive::Explosive(RenderData * _RD, std::string _filename, SpawnHandler* _spawner) : Throwable(_RD, _filename, _spawner)
{
	RD_ptr = _RD;
	m_spawner = _spawner;
}

Explosive::~Explosive()
{
}

void Explosive::Tick(GameStateData * _GSD)
{
	Item::Tick(_GSD);
	if (m_active)
	{
		m_fuse -= _GSD->m_dt;
	}

	if (m_state == ItemState::HELD)
	{
		m_pos = player_ignore->GetPos();
	}

	if (m_explode == true)
	{
		Explosion* explosion = new Explosion(m_pos, RD_ptr, _GSD, m_spawner, m_explosion_range, m_power);
		
		m_spawner->onNotify(this, Event::OBJECT_DESTROYED);

		m_spawner->onNotify(explosion, Event::OBJECT_INSTANTIATED);

		//m_pos = Vector2(1500, 1000);
	
		m_explode = false;
	}


}

void Explosive::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (_collision->GetOwner()->GetTag() == GameObjectTag::YO)
	{
		int i = 0;
	}
	Throwable::CollisionEnter(_collision, _normal);


	if (m_state == ItemState::THROWN 
		&& m_active == true 
		&& _collision->GetOwner()->GetTag() == GameObjectTag::PLAYER
		&& _collision->GetOwner() != player_ignore)
	{
	
		if (m_hit_player == "explode")
		{
			m_explode = true;
		}
	}



}

