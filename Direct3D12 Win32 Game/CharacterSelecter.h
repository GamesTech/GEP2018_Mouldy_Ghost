#pragma once

#include "ImageGO2D.h"

class CharacterSelecter
	: public ImageGO2D
{
public:
	CharacterSelecter(RenderData* _RD, string _filename, GameScene* _gameScene, int _controller);
	~CharacterSelecter() = default;

	void Select();
	void Deselect();
	void Move(int direction);
private:
	int m_controller;
	RenderData* m_RD;
	GameScene* m_GameScene;
	std::vector<std::string> m_all_characters;
	int m_selected_character;
};