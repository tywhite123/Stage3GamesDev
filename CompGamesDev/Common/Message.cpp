#include "Message.h"



//Message::Message(GameEnums::Subsystem to, GameEnums::Subsystem from, GameEnums::MType type, float data)
//{
//	this->to = to;
//	this->from = from;
//	this->type = type;
//	this->data = data;
//}
//
//Message::Message(GameEnums::Subsystem to, GameEnums::MType type, float data = 0)
//{
//	this->to = to;
//	this->type = type;
//	this->data = data;
//}



Message::Message(GameEnums::MType type)
{
	mType = type;
	if (type == GameEnums::Spawn_Tri) {
		/*sysDeliv.push_back(GameEnums::Subsystem::Physics);
		sysDeliv.push_back(GameEnums::Subsystem::Graphics);*/
		sys = GameEnums::Subsystem::Physics;
	}
}

Message::~Message()
{
}
