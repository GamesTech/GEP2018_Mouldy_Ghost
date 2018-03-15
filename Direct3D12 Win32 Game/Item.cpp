#include "pch.h"
#include "Item.h"
#include <fstream>


Item::Item()
{
}

Item::Item(RenderData * _RD, string _filename) : ImageGO2D(_RD,_filename)
{
	m_item_physics = new Physics2D();
	m_item_physics->SetOwner(this);

	tag = GameObjectTag::ITEM;
	
}

Item::~Item()
{
}

void Item::Tick(GameStateData * _GSD)
{
}

void Item::pickUp(Character * _player)
{
	if (m_onPickUp == "use")
	{
		use(_player);
	}
	else if (m_type != ItemType::SINGLE_USE)
	{
		_player->AddChild(this);
		//_player->setHeldItem(this);
		if (m_onPickUp == "activate")
		{
			m_active = true;
		}
	}
}

void Item::use(Character * _player)
{
	//powerups
	
		if (m_onUse == "heal")
		{
			//_player->heal(m_power);
		}
		else if (m_onUse == "hammer_yo")
		{
		
		}
	
}

void Item::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
}

void Item::Collision(Physics2D * _collision)
{
	
	//ignore coll with players

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		//do not fall thru
	}

}

void Item::CollisionExit(Physics2D * _collision)
{
}
