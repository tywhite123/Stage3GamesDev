#include "Message.h"



Message::Message(GameObject & to, GameObject & from, MType type, float data)
{
	this->to = &to;
	this->from = &from;
	this->type = type;
	this->data = data;
}

Message::~Message()
{
}
