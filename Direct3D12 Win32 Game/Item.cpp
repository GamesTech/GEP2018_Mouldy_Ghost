#include "pch.h"
#include "Item.h"
#include <fstream>


Item::Item()
{
}

Item::Item(RenderData * _RD, string _filename) : ImageGO2D(_RD,_filename)
{
	m_physics = new Physics2D();
	m_physics->SetOwner(this);
	m_physics->SetBounce(0.5);
	m_physics->SetGrav(1);

	m_scale =Vector2( 0.1,0.1);

	tag = GameObjectTag::ITEM;
	
}

Item::~Item()
{
}

void Item::Tick(GameStateData * _GSD)
{
	m_physics->Tick(_GSD,m_pos);
	GameObject2D::Tick(_GSD);
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

	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		
		if (m_physics->GetVel().y < 100)
		{
			m_physics->ResetForce(Axis::Y_AXIS);
			m_physics->SetGrav(0);

		}
	}

}

void Item::Collision(Physics2D * _collision)
{
	
	//ignore coll with players

}

void Item::CollisionExit(Physics2D * _collision)
{

}
