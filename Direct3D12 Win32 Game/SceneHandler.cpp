#include "pch.h"
#include "SceneHandler.h"
#include "Scene.h"
#include "TestScene.h"


SceneHandler::SceneHandler()
{
}


SceneHandler::~SceneHandler()
{
}

void SceneHandler::populateScenesList(std::vector<Scene*> _allScenes)
{
	for (int i = 0; i < _allScenes.size(); i++)
	{
		m_allScenes.push_back(_allScenes[i]);
	}
}

void SceneHandler::onNotify(GameObject2D * entity_, Event event_)
{
	switch (event_)
	{
	case Event::CHANGE_SCENE_TEST:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "TestScene")
			{
				m_GSD->objects_in_scene.clear();
				m_activeScene->Reset();
				*m_activeScene = *m_allScenes[i];
				m_activeScene->PhysicsInScene(m_GSD);
			}
		}
	case Event::CHANGE_SCENE_PHYSICS:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "PhysicsScene")
			{
				m_GSD->objects_in_scene.clear();
				m_activeScene->Reset();
				*m_activeScene = *m_allScenes[i];
				m_activeScene->PhysicsInScene(m_GSD);
			}
		}
		break;
	default:
		break;
	}
}
