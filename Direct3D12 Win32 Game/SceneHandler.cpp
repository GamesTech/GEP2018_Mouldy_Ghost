#include "pch.h"
#include "SceneHandler.h"
#include "Scene.h"


SceneHandler::SceneHandler()
{
}


SceneHandler::~SceneHandler()
{
}

void SceneHandler::init(GameStateData * _GSD , std::vector<Scene*> _allScenes)
{
	m_GSD = _GSD;

	for (int i = 0; i < _allScenes.size(); i++)
	{
		m_allScenes.push_back(_allScenes[i]);
		m_allScenes[i]->Reset();

	}
	for (int i = 0; i < m_allScenes.size(); i++)
	{
		if (m_allScenes[i]->getType() == "MenuScene")
		{
			m_activeScene = m_allScenes[i];
		}
	}
}

void SceneHandler::populateScenesList(std::vector<Scene*> _allScenes)
{
	for (int i = 0; i < _allScenes.size(); i++)
	{
		m_allScenes.push_back(_allScenes[i]);
		m_allScenes[i]->Reset();
	}
}

void SceneHandler::addScene(Scene * _scene)
{
	m_allScenes.push_back(_scene);
}

void SceneHandler::onNotify(GameObject2D * entity_, Event event_)
{
	bool sceneChanged = false;
	int sceneChangeIndex;
	switch (event_)
	{
	case Event::CHANGE_SCENE_GAME:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "GameScene")
			{
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
		break;
	case Event::CHANGE_SCENE_MAIN_MENU:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "MenuScene")
			{
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
		break;
	case Event::CHANGE_SCENE_MELEE_MENU:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "MeleeScene")
			{
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
		break;
	case Event::CHANGE_SCENE_CHARACTER_SELECT:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "CharacterScene")
			{
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
		break;
	case Event::CHANGE_SCENE_GAME_SETTINGS:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "GameSettings")
			{
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
		break;
	default:
		break;
	}

	if (sceneChanged)
	{
		m_GSD->objects_in_scene.clear();
		m_activeScene = m_allScenes[sceneChangeIndex];
		m_activeScene->PhysicsInScene(m_GSD);
		m_activeScene->Reset();
	}
}
