#include "pch.h"
#include "Item.h"


Item::Item()
{
}

Item::Item(RenderData * _RD, string _filename) : ImageGO2D(_RD,_filename)
{
}

Item::~Item()
{
}

void Item::Tick(GameStateData * _GSD)
{
}

void Item::onPickup()
{
}

void Item::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
}

void Item::Collision(Physics2D * _collision)
{
	if (state == ItemState::WAIT)
	{
		//ignore coll with players
	}
}

void Item::CollisionExit(Physics2D * _collision)
{
}
