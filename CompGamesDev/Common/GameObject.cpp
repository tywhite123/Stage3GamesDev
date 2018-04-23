#include "GameObject.h"


GameObject::GameObject(float x, float y)
{
	objectPos.x = x;
	objectPos.y = y;
}

GameObject::GameObject(float x, float y, float depth, float rot, float sX, float sY, std::string type, std::string shape, std::string tex)
{
	objectPos = Vector3(x, y, depth);
	rotation = rot;
	scale = Vector2(sX, sY);

	if (type == "Player")
		objType = ObjectType::Player;
	else if (type == "Enemy")
		objType = ObjectType::Enemy;
	else if (type == "Map")
		objType = ObjectType::Map;
	else if (type == "Wall")
		objType = ObjectType::Wall;
	else if (type == "Door")
		objType = ObjectType::Door;

	shapeType = shape;
	texPath = tex;

}

GameObject::~GameObject()
{
}

