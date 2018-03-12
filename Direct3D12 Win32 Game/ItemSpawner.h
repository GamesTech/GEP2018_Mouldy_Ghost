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

	void loadAllData();
	void advanceFile(std::ifstream& _opened_file);

private:
	std::vector<Item*> allItems;
};

//Item * newInstance = new Item(original_instance) ->makes a copy


