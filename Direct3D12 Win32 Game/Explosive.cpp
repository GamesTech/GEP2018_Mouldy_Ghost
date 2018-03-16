#include "pch.h"
#include "Explosive.h"
#include "GameStateData.h"

Explosive::Explosive()
{
}

Explosive::Explosive(RenderData * _RD, std::string _filename) : Throwable(_RD, _filename)
{
}

Explosive::~Explosive()
{
}

void Explosive::Tick(GameStateData * _GSD)
{
	if (m_active)
	{
		m_fuse -= _GSD->m_dt;
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
			float tmp = m_physics->GetVel().y;
			m_physics->ResetForce(Axis::Y_AXIS);
			m_physics->AddForce(Vector2(0,-tmp));
		}
		else if (m_hit_ground == "stick")
		{
			m_physics->ResetForce(Axis::BOTH_AXES);
			_collision->GetOwner()->AddChild(this);
		}
	}

}

