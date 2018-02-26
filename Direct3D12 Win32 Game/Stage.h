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
	void render(RenderData* _RD);

protected:

	std::vector<GameObject2D*> other_objects;
	std::vector<Platform*> platforms; 
	std::vector<Vector2> spawn_points;

	float elapsed_time;

};

