#pragma once

#include <nclgl\Vector2.h>
#include <nclgl\Vector3.h>
#include <string>


enum ObjectType {
	Player, Map, Enemy, Wall, Door
};

class GameObject
{
public:
	GameObject(float x, float y);
	GameObject(float x, float y, float depth, float rot, float sX, float sY, std::string type, std::string shape, std::string tex);
	~GameObject();

	float getXPos() { return objectPos.x; }
	void setXPos(float x) { objectPos.x = x; }

	float getYPos() { return objectPos.y; }
	void setYPos(float y) { objectPos.y = y; }

	float getRotation() { return rotation; }
	void setRotation(float r) { rotation = r; }

	Vector3 getPos() { return objectPos; }

	Vector2 getScale() { return scale; }

	ObjectType getType() { return objType; }
	
	std::string getTexPath() { return texPath; }

	std::string getShape() { return shapeType; }

protected:
	Vector3 objectPos;
	float rotation;
	Vector2 scale;

	ObjectType objType;

	std::string texPath;
	std::string shapeType;
	
};

