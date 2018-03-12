#include "pch.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner()
{
}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::loadAllData()
{
}

void ItemSpawner::advanceFile(std::ifstream& _opened_file)
{
	while (!_opened_file.eof())
	{
		char tmp = "t";
		_opened_file >> tmp;

		if (tmp == ">")
		{
			return;
		}
	}
}

void ItemSpawner::loadAllData()
{
}