#include "MessageQueue.h"



MessageQueue::MessageQueue(std::vector<GameObject*>& objects)
{
	this->obj = &objects;
}


MessageQueue::~MessageQueue()
{
}

Message* MessageQueue::getMessage(GameEnums::Subsystem sys)
{
	Message* m;
	for (int i = 0; i < messageQueue.size(); ++i) {
		m = messageQueue.at(i);

		if (m) {
			if (m->getSys() == sys) {
				return m;
			}
		}
	}
	
	return &Message();
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
