#include "pch.h"

#include "Stage.h"
#include "GameStateData.h"

Stage::Stage()
{
	spawn[0] = Vector2(-100, -100);
	spawn[1] = Vector2(150, -100);
	spawn[2] = Vector2(700, 100);
	spawn[3] = Vector2(400, 100);
}

Stage::~Stage()
{
	for (auto& platform : platforms)
	{
		delete platform;
		platform = nullptr;
	}

	platforms.clear();
}

void Stage::update(GameStateData* _GSD)
{
	
}

void Stage::init(RenderData * _RD, GameStateData * _GSD)
{
}

void Stage::addObjectsToScene(std::vector<GameObject2D*>& _g_objects, GameStateData* _GSD)
{
	for (int i = 0; i < platforms.size(); i++)
	{
		_g_objects.push_back(platforms[i]);
		_GSD->objects_in_scene.push_back(platforms[i]->GetPhysics());
	}
	for(int i = 0; i < other_objects.size(); i++)
	{
		_g_objects.push_back(other_objects[i]);
		_GSD->objects_in_scene.push_back(other_objects[i]->GetPhysics());
	}
}

void Stage::addPlatform(Platform * _platform)
{
	platforms.push_back(_platform);
}

void Stage::setSpawnPointAtIndex(int _i, Vector2 point)
{
	spawn[_i] = point;
}

Vector2 Stage::getRandomSpawnPoint()
{
	return spawn[rand() % 4];
}
