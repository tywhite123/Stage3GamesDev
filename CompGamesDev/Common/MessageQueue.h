#pragma once
#include <vector>
#include "Message.h"

class MessageQueue
{
public:
	MessageQueue(std::vector<GameObject*>& objects);
	~MessageQueue();

	void addMessage(Message* m) {
		messageQueue.push_back(m);
	}

	int getMessage(GameEnums::Subsystem sys);

	void dispatchMessages();

	std::vector<Message*> getQueue() {
		return messageQueue;
	}


protected:
	std::vector<GameObject*>* obj;
	std::vector<Message*> messageQueue;
};

