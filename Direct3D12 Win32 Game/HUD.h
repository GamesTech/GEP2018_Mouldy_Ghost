#pragma once

#include "Characters.h"

//Hold a character and whether they exist in the scene
struct InScene
{
	Character* character;
	bool in_game;
};

class HUD
{
public:
	HUD() = default;
	HUD(GameStateData* _GSD);
	~HUD();

	void AddCharacter(Character* _char);
	void RemoveCharacter(Character* _char);

	//The game's timer is passed in using this pointer
	void attachTimerPointer(float* _timer);

	void Render(RenderData* _RD);
private:
	InScene m_in_game[4];          //a character and a bool pertaining to whether they're present in the game
	Text2D* m_text_display[4];     //lives and damage on characters
	Text2D* m_highlight[4];        //rendered behind the text to make it stand out
	Text2D* m_shadow[4];           //rendered behind the text to make it stand out
	Text2D* m_timeText = nullptr;  //displays time left in game

	float* m_timer;

};