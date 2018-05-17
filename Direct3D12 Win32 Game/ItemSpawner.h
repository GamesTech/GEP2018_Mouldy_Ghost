#pragma once
#include "Item.h"
#include "Explosive.h"
#include "Throwable.h"
#include "MeleeWeapon.h"


class ItemSpawner
{
public:
	ItemSpawner() = default;
	ItemSpawner(SpawnHandler* _spawner);
	~ItemSpawner();

	//loading stuff
	void loadAllData(RenderData* _RD);
	void loadItem(RenderData* _RD, std::string item_file);
	void loadAllItemProperies(Item* item, std::ifstream& _opened_file);
	void loadThrowableProperies(Throwable* item, std::ifstream& _opened_file);
	void loadExplosiveProperies(Explosive* item, std::ifstream& _opened_file);
	void loadMeleeWeaponProperties(MeleeWeapon* item, std::ifstream& _opened_file);

	Item* createNewItemWithName(RenderData* _RD, std::string name);
	std::string getRandomItemName();

	/*
	Go trough the list of all loaded items and assign their availability
	Availability indicates if the specifi item can spawn or not
	The availability is set in the GameSettingsScene

	*/
	void assignAvailability(std::vector<bool> _available_items);
private:
	
	SpawnHandler* m_spawner;
	std::vector<Item*> allItems;
};

//Item * newInstance = new Item(original_instance) ->makes a copy


