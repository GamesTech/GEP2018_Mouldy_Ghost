#pragma once
#include "EventHandler.h"
class GameSettingsHandler :
	public EventHandler
{
public:
	GameSettingsHandler();
	~GameSettingsHandler();
	virtual void onNotify(GameObject2D* entity_, Event event_) override;
    
	virtual std::string getType() { return "GameSettings"; };

	int getLives();
	float getTime();
	bool getInfiniteTime();
	bool getInfiniteLives();
	std::vector<bool> available_items;

private:
	int m_lives;
	float m_time;
	bool m_infiniteTime;
	bool m_infiniteLives;
};

