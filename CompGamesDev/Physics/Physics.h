#pragma once

#include <Box2D\Box2D.h>
#include <map>
#include <vector>
#include <Common\GameObject.h>
#include <Common\MessageQueue.h>

class Physics
{
public:
	Physics(std::vector<GameObject*>& objects, MessageQueue &queue);
	~Physics();

	void PhysicsUpdate(float msec);
	void NewObject();
	void UpdateMessage();

protected:
	b2Vec2 gravity = b2Vec2(0.0, -10.0f);
	b2World world = b2World(gravity);
	

	std::map<GameObject*, b2Body*> obj;
	MessageQueue* mQueue;
	std::vector<GameObject*>* objList;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};

