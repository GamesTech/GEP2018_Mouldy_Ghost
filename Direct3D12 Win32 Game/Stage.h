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
	virtual void init(RenderData* _RD,GameStateData* _GSD);

	void addObjectsToScene(std::vector<GameObject2D*>& _g_objects, GameStateData* _GSD);
	void addPlatform(std::shared_ptr<Platform> _platform);
	void setSpawnPointAtIndex(int _i, Vector2 point);

	const Vector2 getSpawn(int i) { return spawn[i]; }
	void setName(std::string _name) { name = _name; }
	std::string getName() { return name; }

	Vector2 getRandomSpawnPoint();
protected:

	std::string name = "stage";

	std::vector<GameObject2D*> other_objects;
	std::vector<std::shared_ptr<Platform>> platforms;


	float elapsed_time;

	Vector2 spawn[4];
};

