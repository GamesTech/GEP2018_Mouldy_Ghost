#pragma once
#include "Item.h"

class Player2D;

class Throwable: public Item
{
public:
	Throwable();
	~Throwable();

	void loadItemData() override;

	void Throw(Player2D* _player);
	virtual void use(Player2D* _player) override;

	void Collision(Physics2D* _collision);

protected:
	Player2D * player_ignore = nullptr;

	std::string m_on_throw;
	std::string m_hit_player;
	std::string m_hit_ground;
	
	
};

