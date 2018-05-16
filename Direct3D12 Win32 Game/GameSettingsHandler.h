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
	void addAvailableItemSlot();
	int getStageSelected() { return m_stage_selected; }



	bool isStageSelected() { return m_is_stage_selected; }
	void setIsStageSelected(bool _selected) { m_is_stage_selected = _selected; }

private:
	int m_lives;
	float m_time;
	bool m_infiniteTime;
	bool m_infiniteLives;
	std::vector<bool> available_items;

	bool m_is_stage_selected = false;
	int m_stage_selected = -1;
	
};

