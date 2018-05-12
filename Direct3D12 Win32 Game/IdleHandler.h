#pragma once
#include "StepTimer.h"
#include "Events.h"
#include "EventHandler.h"

class IdleHandler
{
public:
	IdleHandler() = default;
	~IdleHandler() = default;

    /*
    This class is used to count how much time it has been since
    input was last received.
    
    seconds         - how much time has passed since the last update was called
    _switch_to_call - what happens in the game when too much time has passed being idle
    _input          - has the game received input since last frame
    _event_handlers - points to the event handlers, to call events when necessary
    max_time        - how long can this scene be idle before the event is called
    */
	void update(float seconds, Event _switch_to_call, bool & _input,
		std::vector<EventHandler*>* _event_handlers, float max_time);
	void reset() { m_time_passed = 0; }
private:
    //measures the time since last input
	float m_time_passed = 0;
};