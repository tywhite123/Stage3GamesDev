#pragma once

#include <nclgl\Vector2.h>

class GameObject
{
public:
	GameObject(float x, float y);
	~GameObject();

	float getXPos() { return objectPos.x; }
	void setXPos(float x) { objectPos.x = x; }

	float getYPos() { return objectPos.y; }
	void setYPos(float y) { objectPos.y = y; }

protected:
	Vector2 objectPos;
};

