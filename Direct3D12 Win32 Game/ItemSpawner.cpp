#include "pch.h"
#include "ItemSpawner.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

ItemSpawner::ItemSpawner()
{
}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::loadAllData(RenderData* _RD)
{
	std::ifstream all_items_file;
	all_items_file.open("..\\GameAssets\\Items\\All_Items.txt");

	assert(all_items_file);
	while (!all_items_file.eof())
	{
		std::string item = getFileData(all_items_file);
		loadItem(_RD,item);

	}

	all_items_file.close();
}

void ItemSpawner::loadItem(RenderData* _RD, std::string _item_file)
{
	std::string file_string = "..\\GameAssets\\Items\\" + _item_file + ".txt";
	std::ifstream item_file;
	item_file.open(file_string);

	std::string type = getFileData(item_file);
	std::string image = getFileData(item_file);

	Item* loaded_item = nullptr;
	if (type == "single_use")
	{
		Item* tmp = new Item(_RD,image);
		tmp->setitemType(ItemType::SINGLE_USE);
		loadAllItemProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "throwable")
	{
		Throwable* tmp = new Throwable(_RD, image);
		tmp->setitemType(ItemType::THROWABLE);
		loadAllItemProperies(tmp, item_file);
		loadThrowableProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "explosive")
	{
		Explosive* tmp = new Explosive(_RD, image);
		tmp->setitemType(ItemType::EXPLOSIVE);
		loadAllItemProperies(tmp, item_file);
		loadThrowableProperies(tmp, item_file);
		loadExplosiveProperies(tmp, item_file);

		loaded_item = tmp;
	}

	allItems.push_back(loaded_item);

	item_file.close();
}


void ItemSpawner::loadAllItemProperies(Item * item, std::ifstream & _opened_file)
{

	//name
	item->SetName(getFileData(_opened_file));

	//pickup
	item->setOnPickupString(getFileData(_opened_file));

	//use
	item->setOnUseString(getFileData(_opened_file));

	//power
	item->setPower(std::stof(getFileData(_opened_file)));
}

void ItemSpawner::loadThrowableProperies(Throwable * item, std::ifstream & _opened_file)
{
	//throw
	item->setOnThrowString(getFileData(_opened_file));

	//hit player
	item->setOnHitPlayerString(getFileData(_opened_file));
	
	//hit ground
	item->setOnHitGroundString(getFileData(_opened_file));
}

void ItemSpawner::loadExplosiveProperies(Explosive * item, std::ifstream & _opened_file)
{
	//fuse
	item->setFuse(std::stof(getFileData(_opened_file)));

	//fuse
	item->setExpRange(std::stof(getFileData(_opened_file)));

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

	assert(false);
	//if assert you entered name that does not exist

}

