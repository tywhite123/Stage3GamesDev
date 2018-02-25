#pragma once
#include <vector>
#include "Message.h"

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	void addMessage(Message m) {
		messageQueue.push_back(m);
	}

	void dispatchMessages();


protected:
	std::vector<Message> messageQueue;
};

