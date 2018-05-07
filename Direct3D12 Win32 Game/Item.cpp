#include "pch.h"
#include "Item.h"
#include <fstream>
#include "SpawnHandler.h"

#include "VisiblePhysics.h"

Item::Item()
{
}

Item::Item(RenderData * _RD, string _filename, SpawnHandler* _spawner) : ImageGO2D(_RD,_filename)
{
	m_handler = _spawner;
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics = new Physics2D();
#endif;
	m_physics->SetOwner(this);
	m_physics->SetBounce(0.5);
	m_physics->SetGrav(1);

	tag = GameObjectTag::ITEM;
	
}

Item::Item(Item * item_to_copy, RenderData* _RD, string _filename, SpawnHandler* _spawner) : Item(_RD, _filename, _spawner) //call standard constructor to create physics and image
{
	//all items need to have these
	m_type = item_to_copy->getitemType();

	name = item_to_copy->GetName();
	m_onPickUp = item_to_copy->getOnPickupString();
	m_onUse = item_to_copy->getOnUseString();
	m_power = item_to_copy->getPower();
	
	
}

Item::~Item()
{
	if (m_physics)
	{
		delete m_physics;
		m_physics = nullptr;
	}
}

void Item::Tick(GameStateData * _GSD)
{
	m_physics->Tick(_GSD,m_pos);
	GameObject2D::Tick(_GSD);


}

void Item::pickUp(Character * _player)
{
	
	if (m_onPickUp == "use") //singe used items are used immediately on pickup and then destroyed
	{
		use(_player);
		m_handler->onNotify(this, Event::OBJECT_DESTROYED);
	}
	else if (m_type != ItemType::SINGLE_USE) //every other item type gets equipped
	{
		_player->AddChild(this);
		//m_physics->SetGrav(0);
		//player->equip items
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
			_player->TakeDamage(-m_power); 
		}
		else if (m_onUse == "hammer")
		{
		
		}
		else if (m_onUse == "strength_up")
		{
			Buff* buff = new Buff(BuffType::STRENGHT_BUFF, _player, m_power);
			_player->BuffCharacter(buff);
		}
	
}

void Item::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	//no bouncing, simply stop and wait to be picked up
	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		m_physics->ResetForce(Axis::Y_AXIS);
		m_physics->SetGrav(0);
	}
}

void Item::Collision(Physics2D * _collision)
{
	
	//ignore coll with players

}

void Item::CollisionExit(Physics2D * _collision)
{

}
