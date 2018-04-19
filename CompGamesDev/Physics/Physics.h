#pragma once

#include <Box2D\Box2D.h>
#include <map>
#include <vector>
#include <Common\GameObject.h>
#include <Common\EventQueue.h>

class Physics
{
public:
	Physics(std::vector<GameObject*>& objects, EventQueue* eq);
	~Physics();

	void PhysicsUpdate(float msec);
	void NewObject();

	void RecieveEvent();



	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Physics; }


protected:
	b2Vec2 gravity = b2Vec2(0.0, 0.0f);
	b2World world = b2World(gravity);
	
	b2ContactListener contactListener;

	std::map<GameObject*, b2Body*> obj;
	std::vector<GameObject*>* objList;
	EventQueue* eQueue;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

};

