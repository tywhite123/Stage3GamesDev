#pragma once

#include <Box2D\Box2D.h>
#include <map>
#include <vector>
#include "..\CompGamesDev\GameObject.h"

class Physics
{
public:
	Physics(std::vector<GameObject*>& objects);
	~Physics();

	void PhysicsUpdate(float msec);

protected:
	b2Vec2 gravity = b2Vec2(0.0, -10.0f);
	b2World world = b2World(gravity);
	b2Body* groundBody;
	b2Body* body;

	std::map<b2Body*, GameObject*> obj;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};

