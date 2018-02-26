#pragma once
#include "EventHandler.h"
class SceneHandler :
	public EventHandler
{
public:
	SceneHandler();
	~SceneHandler();
	virtual void onNotify(GameObject2D* entity_, Event event_) override;
};

