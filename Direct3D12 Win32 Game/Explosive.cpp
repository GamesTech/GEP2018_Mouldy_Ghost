#include "pch.h"
#include "Explosive.h"

Explosive::Explosive()
{
}

Explosive::~Explosive()
{
}

void Explosive::Tick(GameStateData * _GSD)
{
	if (m_active)
	{
	//	m_fuse -= _GSD.m_dt;
	}

	if (m_explode == true)
	{
		//create explosion
		//push it back to game state data

		
	}
}

void Explosive::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (m_state == ItemState::THROWN 
		|| m_active == true 
		&& _collision->GetOwner()->GetTag() == GameObjectTag::PLAYER
		&& _collision->GetOwner() != player_ignore)
	{
		if (m_hit_player == "bounce")
		{
			//hit the player
			//and bounce
		}
		if (m_hit_player == "explode")
		{
			m_explode = true;
		}
	}

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		player_ignore = nullptr;

		if (m_hit_ground == "bounce")
		{
			//m_item_physics->GetVel();
		}
		else if (m_hit_ground == "stick")
		{
			m_item_physics->ResetForce(Axis::BOTH_AXES);
			_collision->GetOwner()->AddChild(this);
		}
	}

}

