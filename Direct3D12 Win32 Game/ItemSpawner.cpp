#include "pch.h"
#include "ItemSpawner.h"
#include <fstream>

ItemSpawner::ItemSpawner()
{
}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::loadAllData()
{
	std::ifstream all_items_file;
	all_items_file.open("GameAssets//ItemFiles//All_Items");

	while (!all_items_file.eof())
	{
		advanceFile(all_items_file);
		std::string item;
		all_items_file >> item;

		loadItem(item);
	}
}

void ItemSpawner::loadItem(std::string _item_file)
{
	std::string file_string = "GameAssets//ItemFiles//" + _item_file;
	std::ifstream item_file;
	item_file.open(file_string);

	std::string type;
	advanceFile(item_file);
	item_file >> type;

	Item* loaded_item = nullptr;
	if (type == "single_use")
	{
		Item* tmp = new Item();
		tmp->setitemType(ItemType::SINGLE_USE);
		loadAllItemProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "throwable")
	{
		Throwable* tmp = new Throwable();
		tmp->setitemType(ItemType::THROWABLE);
		loadAllItemProperies(tmp, item_file);
		loadThrowableProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "explosive")
	{
		Explosive* tmp = new Explosive();
		tmp->setitemType(ItemType::EXPLOSIVE);
		loadAllItemProperies(tmp, item_file);
		loadThrowableProperies(tmp, item_file);
		loadExplosiveProperies(tmp, item_file);

		loaded_item = tmp;
	}

	allItems.push_back(loaded_item);
}

void ItemSpawner::advanceFile(std::ifstream& _opened_file)
{
	while (!_opened_file.eof())
	{
		char tmp = '\0';
		_opened_file >> tmp;

		if (tmp == '>')
		{
			return;
		}
	}
}

void ItemSpawner::loadAllItemProperies(Item * item, std::ifstream & _opened_file)
{
	std::string tmp_string;

	//name
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->SetName(tmp_string);

	//pickup
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->setOnPickupString(tmp_string);

	//use
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->setOnUseString(tmp_string);

	//power
	advanceFile(_opened_file);
	float tmp_power;
	_opened_file >> tmp_power;
	item->setPower(tmp_power);
}

void ItemSpawner::loadThrowableProperies(Throwable * item, std::ifstream & _opened_file)
{
	std::string tmp_string;

	//throw
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->setOnThrowString(tmp_string);

	//hit player
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->setOnHitPlayerString(tmp_string);
	
	//hit ground
	advanceFile(_opened_file);
	_opened_file >> tmp_string;
	item->setOnHitGroundString(tmp_string);
}

void ItemSpawner::loadExplosiveProperies(Explosive * item, std::ifstream & _opened_file)
{
	float tmp_float;

	//fuse
	advanceFile(_opened_file);
	_opened_file >> tmp_float;
	item->setFuse(tmp_float);

	//fuse
	advanceFile(_opened_file);
	_opened_file >> tmp_float;
	item->setExpRange(tmp_float);

}

Item* ItemSpawner::createNewItemWithName(std::string name)
{
	for (int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i]->GetName() == name)
		{
			Item* newitem = new Item(*allItems[i]);
			return newitem;
		}
	}
}

