#pragma once
#include "Item.h"
#include "Explosive.h"
#include "Throwable.h"
#include "MeleeWeapon.h"
#include <fstream>

class ItemSpawner
{
public:
	ItemSpawner();
	~ItemSpawner();

	//loading stuff
	void loadAllData();
	void loadItem(std::string item_file);
	void advanceFile(std::ifstream& _opened_file);
	void loadAllItemProperies(Item* item, std::ifstream& _opened_file);
	void loadThrowableProperies(Throwable* item, std::ifstream& _opened_file);
	void loadExplosiveProperies(Explosive* item, std::ifstream& _opened_file);






	Item* createNewItemWithName(std::string name);

private:
	std::vector<Item*> allItems;
};

//Item * newInstance = new Item(original_instance) ->makes a copy


