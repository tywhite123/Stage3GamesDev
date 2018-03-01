#include "MessageQueue.h"



MessageQueue::MessageQueue(std::vector<GameObject*>& objects)
{
	this->obj = &objects;
}


MessageQueue::~MessageQueue()
{
}

int MessageQueue::getMessage(GameEnums::Subsystem sys)
{
	for (int i = 0; i < messageQueue.size(); ++i) {
		if (messageQueue.at(i)->getSys() == sys) {
			return i;
		}
	}
}

//void MessageQueue::dispatchMessages()
//{
//	Message* m;
//	for (int i = 0; i < messageQueue.size(); ++i)
//	{
//		m = messageQueue.at(i);
//		
//		if (m) {
//			GameEnums::Subsystem subsys = m->GetTo();
//		}
//
//	}
//
//	messageQueue.clear();
//
//}
