#pragma once
#include "ImageGO2D.h"
#include "ItemState.h"
#include "Physics2D.h"
#include "SpawnHandler.h"

class Item :public ImageGO2D
{
public:
	Item();
	/* Items get loaded n from a text file 
	The data read from the files gets saved into variables
	The variables say how should the item behave in certain scenarios*/
	Item(RenderData* _RD, string _filename, SpawnHandler* _spawner);

	/*
	*copy constructor
	*used for cloning
	*creates a new instance and sets appropriate variables to what they should be
	*/
	Item(Item* item_to_copy, RenderData* _RD, string _filename, SpawnHandler* _spawner); 

	virtual ~Item();

	virtual void Tick(GameStateData* _GSD);


	virtual void pickUp(Character* _player);

	/*
	Use gets called on player input 

	*/
	virtual void use(Character* _player);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void CollisionExit(Physics2D* _collision)override;

	void setOnPickupString(std::string _pickup) { m_onPickUp = _pickup; }
	void setOnUseString(std::string _use) { m_onUse = _use; }
	void setPower(float _power) { m_power = _power; }
	void setitemType(ItemType type) { m_type = type; }

	std::string getOnPickupString() { return m_onPickUp; }
	std::string getOnUseString() {return m_onUse; }
	float getPower() { return m_power; }
	
	bool getAvailable() { return m_available; }
	void setAvailable(bool _av) { m_available = _av; }

	ItemType getitemType() { return m_type; }

	SpawnHandler* m_handler;
protected:
	//Availability indicates if the specific item can spawn or not
	bool m_available = true;

	SpawnHandler* m_spawner = nullptr;

	ItemState m_state = ItemState::SPAWNED;
	ItemType m_type = ItemType::SINGLE_USE;

	float m_elapsed_time = 0;
	bool m_active = true;
	float m_power = 0;

	std::string m_onPickUp;
	std::string m_onUse;

};

