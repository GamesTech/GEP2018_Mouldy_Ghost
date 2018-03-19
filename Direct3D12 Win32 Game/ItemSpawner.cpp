#include "pch.h"
#include "ItemSpawner.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

ItemSpawner::ItemSpawner(SpawnHandler* _spawner)
{
	m_spawner = _spawner;
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
		Item* tmp = new Item(_RD,image, m_spawner);
		tmp->setitemType(ItemType::SINGLE_USE);
		loadAllItemProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "throwable")
	{
		Throwable* tmp = new Throwable(_RD, image, m_spawner);
		tmp->setitemType(ItemType::THROWABLE);
		loadAllItemProperies(tmp, item_file);
		loadThrowableProperies(tmp, item_file);

		loaded_item = tmp;
	}
	else if (type == "explosive")
	{
		Explosive* tmp = new Explosive(_RD, image, m_spawner);
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

Item* ItemSpawner::createNewItemWithName(RenderData* _RD, std::string name)
{
	//copy every proprety of an item and then create a new one

	for (int i = 0; i < allItems.size(); i++)
	{
		if (allItems[i]->GetName() == name)
		{
			
			
			ItemType tmptype = allItems[i]->getitemType();
			Item* orig_item = allItems[i];

			Item* newitem = nullptr;
		
			if (tmptype == ItemType::EXPLOSIVE)
			{
				Explosive* orig_item_cast = static_cast<Explosive*>(orig_item);
				Explosive* tmpex = new Explosive(_RD,name);


				tmpex->setOnHitGroundString(orig_item_cast->getOnHitGroundString());
				tmpex->setOnHitPlayerString(orig_item_cast->getOnHitPlayerString());
				newitem = tmpex;
				tmpex->setExpRange(orig_item_cast->getExpRange());
				tmpex->setFuse(orig_item_cast->getFuse());

				tmpex->setOnThrowString(orig_item_cast->getOnThrowString());
			else if (tmptype == ItemType::EXPLOSIVE)
			}
			{
				Throwable* orig_item_cast = static_cast<Throwable*>(orig_item);
				Throwable* tmptr = new Throwable(_RD, name);

				tmptr->setOnHitGroundString(orig_item_cast->getOnHitGroundString());
				tmptr->setOnHitPlayerString(orig_item_cast->getOnHitPlayerString());
				tmptr->setOnThrowString(orig_item_cast->getOnThrowString());

				newitem = tmptr;
			}
			else
			{
				newitem = new Item(_RD, name);
			}
			Rectangle collider = Rectangle
			(newitem->GetPos().x, newitem->GetPos().y, 
				newitem->TextureSize().x, newitem->TextureSize().y);
				newitem->GetPhysics()->SetCollider(collider);


			newitem->setOnPickupString(orig_item->getOnPickupString());
			newitem->setOnUseString(orig_item->getOnUseString());
			newitem->setPower(orig_item->getPower());
	
			return newitem;
		}
	}

	assert(false);
	//if assert you entered name that does not exist
	return nullptr;
}

