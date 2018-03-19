#pragma once

#include "Characters.h"

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

	void Render(RenderData* _RD);
private:
	InScene m_in_game[4];
	Text2D* m_text_display[4];
	Text2D* m_highlight[4];
	Text2D* m_shadow[4];
};