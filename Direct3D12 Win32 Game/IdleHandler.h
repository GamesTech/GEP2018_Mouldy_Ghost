#pragma once
#include "Scene.h"

class IdleHandler
{
public:
	IdleHandler() = default;
	~IdleHandler() = default;

	void update(DX::StepTimer const & timer, Event _switch_to_call,
		bool& _input, std::vector<EventHandler*>* _event_handlers, float max_time = 30.0f);
private:
	float m_time_passed = 0;
};