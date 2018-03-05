#pragma once
#include "ImageGO2D.h"
#include "ItemState.h"

class Item :public ImageGO2D
{
public:
	Item();
	Item(RenderData* _RD, string _filename);
	~Item();

	virtual void Tick(GameStateData* _GSD);

	virtual void onPickup();

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision) override;
	void CollisionExit(Physics2D* _collision)override;


private:
	ItemState state = ItemState::WAIT;
};

