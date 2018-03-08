#pragma once
#include "ImageGO2D.h"
#include "ItemState.h"
#include "Physics2D.h"

class Item :public ImageGO2D
{
public:
	Item();
	Item(RenderData* _RD, string _filename);
	~Item();

	virtual void Tick(GameStateData* _GSD);
	virtual void loadItemData();

	virtual void onPickup(Player2D* player);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision) override;
	void CollisionExit(Physics2D* _collision)override;


protected:
	Physics2D* m_item_physics = nullptr;
	ItemState state = ItemState::WAIT;
	ItemType type = ItemType::SINGLE_USE;
	std::string m_item_name = " ";

};

