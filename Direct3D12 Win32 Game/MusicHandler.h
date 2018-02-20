#pragma once
#include "EventHandler.h"
#include "Events.h"
#include "Loop.h"

class MusicHandler :
	public EventHandler
{
public:
	MusicHandler();
	~MusicHandler();

	virtual void onNotify(GameObject2D * entity, Event event_);

private:

	std::vector<std::shared_ptr<Loop>> allMusic;
};

