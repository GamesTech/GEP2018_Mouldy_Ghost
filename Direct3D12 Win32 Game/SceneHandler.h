#pragma once
#include "EventHandler.h"

class Scene;

class SceneHandler :
	public EventHandler
{
public:
	SceneHandler();
	~SceneHandler();
	void initActiveScene(Scene* _activeScene) { m_activeScene = _activeScene; };
	void populateScenesList(std::vector<Scene*> _allScenes);
	virtual void onNotify(GameObject2D* entity_, Event event_) override;

private:
	std::vector<Scene*> m_allScenes;
	Scene* m_activeScene;
};

