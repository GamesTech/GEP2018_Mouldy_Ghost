#include "pch.h"
#include "IdleHandler.h"

void IdleHandler::update(float seconds, Event _switch_to_call,
	bool& _input, std::vector<EventHandler*>* _event_handlers, float max_time)
{
	if (_input)
	{
		m_time_passed = 0;
		_input = false;
		return;
	}
	m_time_passed += seconds;
	if (m_time_passed >= max_time)
	{
		for (EventHandler* handler : *_event_handlers)
		{
			m_time_passed = 0;
			handler->onNotify(nullptr, _switch_to_call);
		}
	}
}