#include "GamePad.h"
#include "GameStateData.h"
#pragma once
class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	bool playerConfirm(GameStateData * _GSD, int playerIndex);
	bool playerBack(GameStateData * _GSD, int playerIndex);
	//Input A (player number)
	//Input B (player number)
	//Input X (player number)
	//Input Y (player number)
	//Input Left (player number)
	//Input Right (player number)
	//Input Up (player number)
	//Input Down (player number)
	//Send Vibration (player number)
	//Add Score (player number)
	//Use/pickup item (player number)
	//Change Scene
	//Reset Scene
	//Collisions? 
	//Destroy object?
	//messaging to the HUD

};

