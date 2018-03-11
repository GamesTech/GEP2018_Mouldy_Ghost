#pragma once
#include "Item.h"

class Character;

class Throwable: public Item
{
public:
	Throwable();
	~Throwable();

	void loadItemData() override;

	void Throw(Character* _player);
	virtual void use(Character* _player) override;

	void Collision(Physics2D* _collision);

protected:
	Character * player_ignore = nullptr;

	std::string m_on_throw;
	std::string m_hit_player;
	std::string m_hit_ground;
	
	
};

