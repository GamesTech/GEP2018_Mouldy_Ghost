#pragma once
#include "EventHandler.h"

class Scene;

class SceneHandler :
	public EventHandler
{
public:
	SceneHandler();
	~SceneHandler();

	void init(GameStateData * _GSD, std::vector<Scene*> _allScenes);
	void initActiveScene(Scene* _activeScene) { m_activeScene = _activeScene; };
	Scene* getActiveScene() { return m_activeScene; };
	virtual void onNotify(GameObject2D* entity_, Event event_) override;

	virtual std::string getType() override { return "Scene"; }

private:
	std::vector<Scene*> m_allScenes;
	Scene* m_activeScene;
};