#include "Throwable.h"

Throwable::Throwable()
{
}

Throwable::~Throwable()
{
}

void Throwable::loadItemData()
{
}

void Throwable::Throw(Player2D* _player)
{
	player_ignore = _player;

	//_player->get direction?
	// not sure how throw is going to work just yet
	// eeeeh
}

void Throwable::use(Player2D * _player)
{
}

void Throwable::Collision(Physics2D * _collision)
{
	Item::Collision(_collision);

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		player_ignore = nullptr;

		if (m_hit_ground == "bounce")
		{

		}
		else if (m_hit_ground == "stick")
		{

		}
	}
	
}
