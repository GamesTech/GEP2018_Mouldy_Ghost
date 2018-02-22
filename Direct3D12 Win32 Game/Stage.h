#pragma once
#include <vector>
#include "Platform.h"
#include "GameObject2D.h"

class Stage
{
public:
	Stage();
	~Stage();

	virtual void update(float dt) = 0;
	virtual void init() = 0;
	void render(RenderData* _RD);

private:

	std::vector<GameObject2D*> other_objects;
	std::vector<Platform*> platforms; 

};

