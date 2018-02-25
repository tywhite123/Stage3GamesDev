#include "GameObject.h"


GameObject::GameObject(float x, float y)
{
	objectPos.x = x;
	objectPos.y = y;
}

GameObject::~GameObject()
{
}

void GameObject::onMessage(Message m)
{

}
