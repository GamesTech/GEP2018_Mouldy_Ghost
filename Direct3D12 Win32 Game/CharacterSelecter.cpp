#include "pch.h"
#include "CharacterSelecter.h"
#include "GameScene.h"

CharacterSelecter::CharacterSelecter
(RenderData * _RD, string _filename, GameScene * _gameScene, int _controller)
: ImageGO2D(_RD, _filename)
{
	m_RD = _RD;
	m_GameScene = _gameScene;
	m_controller = _controller;
}

void CharacterSelecter::Select()
{
	m_GameScene->AddCharacter
	(m_controller, m_all_characters[m_selected_character], m_RD);
}

void CharacterSelecter::Deselect()
{
	m_GameScene->RemoveCharacter(m_controller);
}

void CharacterSelecter::Move(int direction)
{
	m_selected_character = (m_selected_character + direction)
		% m_all_characters.size();
}
