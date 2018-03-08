#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects, EventQueue* eq) : objList(&objects)
{

	eQueue = eq;

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -12.6f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(objects[0]->getXPos(), objects[0]->getYPos());
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	obj.insert(std::pair<GameObject*, b2Body*>(objects[0], body));

}


Physics::~Physics()
{
}

void Physics::PhysicsUpdate(float msec)
{
	RecieveEvent();
	world.Step(timeStep, velocityIterations, positionIterations);

	/*b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();*/

	/*obj.at(body)->setXPos(obj.at(body)->getXPos() + position.x);
	obj.at(body)->setYPos(position.y);*/

	for (auto o : obj) {
		b2Vec2 position = o.second->GetPosition();
		float32 angle = o.second->GetAngle();

		o.first->setXPos(o.first->getXPos() + position.x);
		o.first->setYPos(o.first->getYPos() + position.y);
		
		printf("%4.2f %4.2f %4.2f\n", o.first->getXPos(), o.first->getYPos(), angle);
	}

	

}

void Physics::NewObject()
{
	GameObject* o = new GameObject(0.0f, 4.0f);
	objList->push_back(o);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(o->getXPos(), o->getYPos());
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);


	obj.insert(std::pair<GameObject*, b2Body*>(o, body));

	printf("New object");
}

void Physics::RecieveEvent()
{
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {

			if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
					objList->at(0)->setXPos(objList->at(0)->getXPos() - 0.01f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
					objList->at(0)->setXPos(objList->at(0)->getXPos() + 0.01f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
					objList->at(0)->setYPos(objList->at(0)->getYPos() + 0.01f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
					objList->at(0)->setYPos(objList->at(0)->getYPos() - 0.01f);
				}

				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


