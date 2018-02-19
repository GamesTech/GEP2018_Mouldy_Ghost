#include "pch.h"
#include "MusicHandler.h"


MusicHandler::MusicHandler()
{
}


MusicHandler::~MusicHandler()
{
}

void MusicHandler::onNotify(GameObject2D * entity, Event event_)
{
	switch (event_)
	{
	case Event::CHANGE_SCENE:
		//code for changing the music goes here?
		break;
	}
}
