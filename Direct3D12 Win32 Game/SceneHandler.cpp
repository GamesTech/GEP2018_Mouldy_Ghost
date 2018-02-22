#include "pch.h"
#include "SceneHandler.h"


SceneHandler::SceneHandler()
{
}


SceneHandler::~SceneHandler()
{
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
