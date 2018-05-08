#pragma once
#include <vector>
#include "Platform.h"
#include "GameObject2D.h"

class Stage
{
public:
	Stage();
	~Stage();

	virtual void update(GameStateData* _GSD);
	virtual void init(RenderData* _RD,GameStateData* _GSD) = 0;

	void addObjectsToScene(std::vector<GameObject2D*>& _g_objects);

	const Vector2 getSpawn(int i) { return spawn[i]; }

	Vector2 getRandomSpawnPoint();
protected:

	std::vector<GameObject2D*> other_objects;
	std::vector<Platform*> platforms; 


	float elapsed_time;

	Vector2 spawn[4];
};

