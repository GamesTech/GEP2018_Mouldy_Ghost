#include "pch.h"
#include "Throwable.h"

Throwable::Throwable()
{
}

Throwable::Throwable(RenderData * _RD, std::string _filename, SpawnHandler* _spawner) : Item(_RD, _filename, _spawner)
{
}

Throwable::~Throwable()
{
}


void Throwable::Throw(Character* _player)
{
	m_physics->SetGrav(1);
	player_ignore = _player;
	m_state = ItemState::THROWN;
	//_player->get direction?
	// not sure how throw is going to work just yet
	// eeeeh

	if (m_on_throw == "activate")
	{
		m_active = true;
	}
}

void Throwable::pickUp(Character * _player)
{
	Item::pickUp(_player);
	player_ignore = _player;

}

void Throwable::use(Character * _player)
{

}

void Throwable::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (m_state == ItemState::THROWN
		&& _collision->GetOwner()->GetTag() == GameObjectTag::PLAYER
		&& _collision->GetOwner() != player_ignore)
	{
		if (m_hit_player == "bounce")
		{
			//hit the player
			//and bounce
		}
	}

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		player_ignore = nullptr;

		if (m_physics->GetVel().y < 100)
		{
			m_physics->ResetForce(Axis::Y_AXIS);
			m_physics->SetGrav(0);

		}
		else if (m_hit_ground == "bounce")
		{
			float tmp = m_physics->GetVel().y;
			m_physics->ResetForce(Axis::Y_AXIS);
			m_physics->AddForce(Vector2(0, -(100 * m_physics->GetBounce()*tmp)));
		}
		else if (m_hit_ground == "stick")
		{
			m_physics->ResetForce(Axis::BOTH_AXES);
			_collision->GetOwner()->AddChild(this);
		}

	
	}

}

void Throwable::Collision(Physics2D * _collision)
{
	Item::Collision(_collision);

	
	
}
