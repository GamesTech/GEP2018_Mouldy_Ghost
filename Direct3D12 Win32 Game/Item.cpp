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
	
	
}

Item::~Item()
{
}

void Item::Tick(GameStateData * _GSD)
{
}

void Item::loadItemData()
{
	//there are going o be different properties for different item types
	//type will indicate how many iteration of for loop here is going to be
}

void Item::pickUp(Character * _player)
{
	
}

void Item::use(Character * _player)
{
	
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
