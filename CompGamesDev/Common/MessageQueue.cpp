#include "MessageQueue.h"



MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

void MessageQueue::dispatchMessages()
{
	Message* m;
	for (int i = 0; i < messageQueue.size(); ++i)
	{
		m = &messageQueue.at(i);
		
		if (m) {
			m->GetTo()->onMessage(*m); 
		}

	}

	messageQueue.clear();

}
