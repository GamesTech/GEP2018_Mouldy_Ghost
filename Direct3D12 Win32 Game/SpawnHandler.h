#pragma once
#include "EventHandler.h"
#include <vector>

enum class ActiveScene
{
	GAME,
	DEMO
};

struct SceneData
{
	RenderData* RD;
	std::vector<GameObject2D*>* objects;
	std::vector<Physics2D*>* physics;
};

class SpawnHandler
	: public EventHandler
{
public:
	SpawnHandler();
	virtual ~SpawnHandler();

	virtual void onNotify(GameObject2D* object, Event _event);
	
	std::string getType() override { return "Spawn"; }

	void setData(std::vector<GameObject2D*>* _2DObjects,
		std::vector<Physics2D*>* _physics, RenderData* _RD,
		ActiveScene _scene);
private:
	SceneData* m_active_data;
	std::unique_ptr<SceneData> m_game_data;
	std::unique_ptr<SceneData> m_demo_data;
};