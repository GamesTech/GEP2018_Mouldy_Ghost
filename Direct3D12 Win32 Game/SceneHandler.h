#pragma once
#include "EventHandler.h"

class Scene;

class SceneHandler :
	public EventHandler
{
public:
	SceneHandler();
	~SceneHandler();

	virtual void init(GameStateData* _GSD) override;
	void initActiveScene(Scene* _activeScene) { m_activeScene = _activeScene; };
	Scene* getActiveScene() { return m_activeScene; };
	void populateScenesList(std::vector<Scene*> _allScenes);
	void addScene(Scene* _scene);
	virtual void onNotify(GameObject2D* entity_, Event event_) override;

private:
	std::vector<Scene*> m_allScenes;
	Scene* m_activeScene;
};

