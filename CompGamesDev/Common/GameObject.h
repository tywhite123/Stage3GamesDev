#pragma once

#include <nclgl\Vector2.h>
#include "Message.h"

class Message;

class GameObject
{
public:
	GameObject(float x, float y);
	~GameObject();

	float getXPos() { return objectPos.x; }
	void setXPos(float x) { objectPos.x = x; }

	float getYPos() { return objectPos.y; }
	void setYPos(float y) { objectPos.y = y; }

	void onMessage(Message m);

protected:
	Vector2 objectPos;
};

