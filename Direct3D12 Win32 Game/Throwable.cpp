#include "pch.h"
#include "Throwable.h"

Throwable::Throwable()
{
}

Throwable::~Throwable()
{
}


void Throwable::Throw(Character* _player)
{
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

void Throwable::Collision(Physics2D * _collision)
{
	Item::Collision(_collision);

	
	
}
