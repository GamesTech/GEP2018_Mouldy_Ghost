#include "pch.h"
#include "Explosive.h"
#include "GameStateData.h"
#include "Explosion.h"

Explosive::Explosive()
{
}

Explosive::Explosive(RenderData * _RD, std::string _filename, SpawnHandler* _spawner) : Throwable(_RD, _filename, _spawner)
{
	//need this for instantiiation of the explosion
	RD_ptr = _RD;
	m_spawner = _spawner;
}

Explosive::Explosive(Item * item_to_copy, RenderData* _RD, string _filename, SpawnHandler* _spawner) : Throwable(item_to_copy,_RD,_filename,_spawner)
{
	Explosive* explosive_ptr = static_cast<Explosive*>(item_to_copy);

	m_fuse = explosive_ptr->getFuse();
	m_explosion_range = explosive_ptr->getExpRange();

	//need this for instantiiation of the explosion
	RD_ptr = _RD;
	m_spawner = _spawner;
}

Explosive::~Explosive()
{
}

void Explosive::Tick(GameStateData * _GSD)
{
	Throwable::Tick(_GSD);

	if (m_active)
	{
		m_fuse -= _GSD->m_dt;
		if (m_fuse < 0)
		{
			m_explode = true;
		}
	}

	
	
	if (m_explode == true)
	{
		//instantiate explosion
		Explosion* explosion = new Explosion(m_pos, RD_ptr, _GSD, m_spawner, m_explosion_range, m_power);
		m_spawner->onNotify(explosion, Event::OBJECT_INSTANTIATED);

		//destroy this
		m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
		  	
		m_explode = false;
	}

	
}

void Explosive::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
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

