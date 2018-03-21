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
	void addScene(Scene* _scene);
	virtual void onNotify(GameObject2D* entity_, Event event_) override;

private:
	std::vector<Scene*> m_allScenes;
	Scene* m_activeScene;
};

