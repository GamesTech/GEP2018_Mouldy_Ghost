#pragma once
#include "ImageGO2D.h"
#include "ItemState.h"
#include "Physics2D.h"
#include "SpawnHandler.h"

class Item :public ImageGO2D
{
public:
	Item();
	Item(RenderData* _RD, string _filename);
	~Item();

	virtual void Tick(GameStateData* _GSD);


	virtual void pickUp(Character* _player);
	virtual void use(Character* _player);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision) override;
	void CollisionExit(Physics2D* _collision)override;

	void setOnPickupString(std::string _pickup) { m_onPickUp = _pickup; }
	void setOnUseString(std::string _use) { m_onUse = _use; }
	void setPower(float _power) { m_power = _power; }
	void setitemType(ItemType type) { m_type = type; }

	std::string getOnPickupString() { return m_onPickUp; }
	std::string getOnUseString() {return m_onUse; }
	float getPower() { return m_power; }
	

	ItemType getitemType() { return m_type; }

protected:
	SpawnHandler* m_spawner = nullptr;

	ItemState m_state = ItemState::WAIT;
	ItemType m_type = ItemType::SINGLE_USE;

	float m_elapsed_time = 0;
	bool m_active = true;
	float m_power = 0;

	std::string m_onPickUp;
	std::string m_onUse;

};

