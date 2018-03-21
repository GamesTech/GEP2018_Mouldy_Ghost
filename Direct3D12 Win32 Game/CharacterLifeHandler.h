#pragma once
#include "EventHandler.h"

class GameOverScene;

class CharacterLifeHandler :
	public EventHandler
{
public:
	CharacterLifeHandler() = default;
	~CharacterLifeHandler() = default;

	virtual void onNotify(GameObject2D* entity_, Event event_) override;
	void SetGameOver(GameOverScene* _go_scene) { m_go_scene = _go_scene; }
private:
	GameOverScene* m_go_scene;
};