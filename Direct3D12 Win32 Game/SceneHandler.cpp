#include "pch.h"
#include "SceneHandler.h"
#include "Scene.h"


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
	case Event::CHANGE_SCENE:
		break;
	default:
		break;
	}
}
