#include "GamePad.h"
#include "GameStateData.h"
#pragma once
class EventHandler
{
public:
	EventHandler();
	~EventHandler();

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
	

	//every gameobject has it's relevent listeners/observer
	//every listener should have a list of the gameobjects is it managing??

	//Example behaviour:
	//player has its collision observer. If it collides with something, it tells the observer.
	//the observer then tells the player what to do and also tells anything else that has to react.
	//does the observer need to tell other observers?
	//I think all relevent observers only need to care about themselves, 
	//it is down to the gameobject that is being listend to, to tell any other observers.

private:
	//no vectors of gameobjects in this base class as there are too many different types of game objects that 
	//don't inherit from any shared base so I can't make use of polymorphism.
};

