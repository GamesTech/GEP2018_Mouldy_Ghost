#include "GamePad.h"
#include "GameStateData.h"
#include "Events.h"
#pragma once

class GameObject2D;

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	virtual void onNotify(GameObject2D* entity_, Event event_) = 0;
	//this is a base class for other eventhandlers/listeners
	//the reason I have made this empty base class is so that 
	//so that listeners can be placed into a vector for every gameobject that need it
	//these are the following children I think will be needed:

	//player handler
	//item handler
	//scene handler
	//collision handler
	//HUD handler
	//achievement handler
	//music handler
	//sound effect handler
	

	//every gameobject has it's relevent listeners/observer

	//Example behaviour:
	//player has its collision observer. If it collides with something, it tells the observer.
	//the observer then tells the player what to do and also tells anything else that has to react.
	//does the observer need to tell other observers?
	//I think all relevent observers only need to care about themselves, 
	//it is down to the gameobject that is being listend to, to tell any other observers.

private:
};

