#pragma once
#include "StepTimer.h"
#include "Events.h"
#include "EventHandler.h"

class IdleHandler
{
public:
	IdleHandler() = default;
	~IdleHandler() = default;

	void update(float seconds, Event _switch_to_call, bool & _input, std::vector<EventHandler*>* _event_handlers, float max_time);
private:
	float m_time_passed = 0;
};