#include "pch.h"
#include "SceneHandler.h"
#include "Scene.h"
#include "GameOverScene.h"


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
		//populate our full list of scenes from the game.cpp
		m_allScenes.push_back(_allScenes[i]);
		m_allScenes[i]->Reset();

	}
	for (int i = 0; i < m_allScenes.size(); i++)
	{
		//go to the menu scene on startup
		if (m_allScenes[i]->getType() == "MenuScene")
		{
			m_activeScene = m_allScenes[i];
		}
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

	//find if we're changing the scene and what scene to change to
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
	case Event::GAME_OVER:
		for (int i = 0; i < m_allScenes.size(); i++)
		{
			if (m_allScenes[i]->getType() == "GameOver")
			{
				static_cast<GameOverScene*>(m_allScenes[i])->SortByScores();
				sceneChanged = true;
				sceneChangeIndex = i;
			}
		}
	default:
		break;
	}

	if (sceneChanged)
	{
		//clear any objects
		m_GSD->objects_in_scene.clear();
		//make our new scene the active scene, set up physics and reset the scene
		m_activeScene = m_allScenes[sceneChangeIndex];
		m_activeScene->PhysicsInScene(m_GSD);
		m_activeScene->Reset();
	}
}