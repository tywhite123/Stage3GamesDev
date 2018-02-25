#pragma once

#include <string>
#include "GameObject.h"

enum MType {
	Test
};


class GameObject;

class Message
{
public:
	Message(GameObject& to, GameObject& from, MType type, float data);
	~Message();

	GameObject* GetTo() { return to; }

protected:
	GameObject* to;
	GameObject* from;
	MType type;
	float data;
};

