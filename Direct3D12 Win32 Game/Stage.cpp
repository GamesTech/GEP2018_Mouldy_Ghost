#include "pch.h"

#include "Stage.h"

Stage::Stage()
{
	spawn[0] = Vector2(-100, -50);
	spawn[1] = Vector2(150, -50);
	spawn[2] = Vector2(700, 100);
	spawn[3] = Vector2(400, 100);
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