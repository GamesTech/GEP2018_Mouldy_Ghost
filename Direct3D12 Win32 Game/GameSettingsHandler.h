#pragma once
#include "EventHandler.h"
class GameSettingsHandler :
	public EventHandler
{
public:
	GameSettingsHandler();
	~GameSettingsHandler();
	virtual void onNotify(GameObject2D* entity_, Event event_) override;

	int getLives();
	float getTime();
	bool getInfinite();

private:
	int m_lives;
	float m_time;
	bool m_infiniteTime;
};

