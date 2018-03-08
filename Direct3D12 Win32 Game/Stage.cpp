#include "pch.h"

#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::update(GameStateData* _GSD)
{
	
}

void Stage::addObjectsToScene(std::vector<GameObject2D*>& _g_objects)
{
	for (int i = 0; i < platforms.size(); i++)
	{
		_g_objects.push_back(platforms[i]);
	}
	for(int i = 0; i < other_objects.size(); i++)
	{
		_g_objects.push_back(other_objects[i]);
	}
}