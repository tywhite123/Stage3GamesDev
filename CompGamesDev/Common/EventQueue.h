#pragma once
#include "Event.h"

class EventQueue
{
public:
	EventQueue();
	~EventQueue();

	void pushEvent(Event* e) {
		events.push_back(e);
	}


	void popEvent() {
		events.pop_back();
	}

	std::vector<Event*> getEvents() {
		return events;
	}

protected:
	std::vector<Event*> events;
};

