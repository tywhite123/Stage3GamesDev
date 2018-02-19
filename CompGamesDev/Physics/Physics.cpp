#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -12.6f);

	groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(objects[0]->getXPos(), objects[0]->getYPos());
	body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	obj.insert(std::pair<b2Body*, GameObject*>(body, objects[0]));

}


Physics::~Physics()
{
}

void Physics::PhysicsUpdate(float msec)
{
	world.Step(timeStep, velocityIterations, positionIterations);

	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	obj.at(body)->setXPos(position.x);
	obj.at(body)->setYPos(position.y);

	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

}
