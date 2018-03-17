#pragma once
#include "EventHandler.h"
#include <vector>

class SpawnHandler
	: public EventHandler
{
public:
	SpawnHandler() = default;
	~SpawnHandler() = default;

	virtual void onNotify(GameObject2D* object, Event _event);

	void setData(std::vector<GameObject2D*>* _2DObjects,
		std::vector<Physics2D*>* _physics, RenderData* _RD);
private:
	RenderData* m_RD;
	std::vector<GameObject2D*>* m_2DObjects;
	std::vector<Physics2D*>* m_physics;
};