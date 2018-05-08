#pragma once
#include "EventHandler.h"
class GameSettingsHandler :
	public EventHandler
{
public:
	GameSettingsHandler();
	~GameSettingsHandler();
	virtual void onNotify(GameObject2D* entity_, Event event_) override;
	virtual void onNotify(int _item_index, Event event_);

	virtual std::string getType() { return "GameSettings"; };

	int getLives();
	float getTime();
	bool getInfiniteTime();
	bool getInfiniteLives();
	std::vector<bool> GetAvailableItems() { return available_items; }

private:
	int m_lives;
	float m_time;
	bool m_infiniteTime;
	bool m_infiniteLives;
	std::vector<bool> available_items;
	
};

