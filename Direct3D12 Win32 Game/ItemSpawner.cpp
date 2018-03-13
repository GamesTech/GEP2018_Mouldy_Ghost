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
		loaded_item = new Item();
		std::string tmp_string;

		//name
		advanceFile(item_file);
		item_file >> tmp_string;
		loaded_item->SetName(tmp_string);

		//pickup
		advanceFile(item_file);
		item_file >> tmp_string;
		loaded_item->setOnPickupString(tmp_string);

		//use
		advanceFile(item_file);
		item_file >> tmp_string;
		loaded_item->setOnUseString(tmp_string);

		//power
		advanceFile(item_file);
		float tmp_power;
		item_file >> tmp_power;
		loaded_item->setPower(tmp_power);


	}
	else if (type == "throwable")
	{
		Throwable* tmp = new Throwable();


		loaded_item = tmp;
	}
	else if (type == "explosive")
	{
		Explosive* tmp = new Explosive();


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

