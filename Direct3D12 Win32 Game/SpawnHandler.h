#pragma once
#include "EventHandler.h"
#include <vector>

class SpawnHander
	: public EventHandler
{
	SpawnHander() = default;
	~SpawnHander() = default;

	virtual void onNotify(GameObject2D* object, Event _event);

private:
	std::vector<GameObject2D*>* _2DObjects;
	std::vector<Physics2D*>* _physics;
};