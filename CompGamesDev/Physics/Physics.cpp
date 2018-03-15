#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects, EventQueue* eq) : objList(&objects)
{

	eQueue = eq;


	///world.SetContactListener(&contactListener);





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
	dynamicBox.SetAsBox(0.125f, 0.125f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	obj.insert(std::pair<GameObject*, b2Body*>(objects[0], body));






	GameObject* o = new GameObject(1.0f, 1.0f);
	objList->push_back(o);
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_dynamicBody;
	bodyDef2.position.Set(o->getXPos(), o->getYPos());
	b2Body* body2 = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox2;
	dynamicBox2.SetAsBox(0.25f, 0.25f);

	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &dynamicBox;

	fixtureDef2.density = 1.0f;

	fixtureDef2.friction = 0.3f;

	body2->CreateFixture(&fixtureDef2);

	obj.insert(std::pair<GameObject*, b2Body*>(objList->at(objList->size() - 1), body2));

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

		o.first->setXPos(position.x);
		o.first->setYPos(position.y);
		
		
		/*for (b2ContactEdge* edge = o.second->GetContactList(); edge; edge = edge->next) {
			b2Vec2 pos = edge->contact->GetFixtureB()->GetBody()->GetPosition();
			printf("%4.2f, %4.2f\n", pos.x, pos.y);
		}*/
		
		//printf("%4.2f %4.2f %4.2f\n", o.first->getXPos(), o.first->getYPos(), angle);
	}

	for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
		printf("Contact");
	}

	

	

}

void Physics::NewObject()
{
	GameObject* o = new GameObject(rand() % 3, rand() % 3);
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

	obj.insert(std::pair<GameObject*, b2Body*>(objList->at(objList->size()-1), body));

	printf("New object");
}

void Physics::RecieveEvent()
{
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {

			if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
					//objList->at(0)->setXPos(objList->at(0)->getXPos() - 0.01f);
					b2Vec2 vel = obj.at(objList->at(i))->GetLinearVelocity();
					vel.x = -0.5f;
					vel.y = 0.0f;
					obj.at(objList->at(i))->SetLinearVelocity(vel);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
					///objList->at(0)->setXPos(objList->at(0)->getXPos() + 0.01f);
					b2Vec2 vel = obj.at(objList->at(i))->GetLinearVelocity();
					vel.x = 0.5f;
					vel.y = 0.0f;
					obj.at(objList->at(i))->SetLinearVelocity(vel);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
					//objList->at(0)->setYPos(objList->at(0)->getYPos() + 0.01f);
					b2Vec2 vel = obj.at(objList->at(i))->GetLinearVelocity();
					vel.x = 0.0f;
					vel.y = 0.5f;
					obj.at(objList->at(i))->SetLinearVelocity(vel);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
					//objList->at(0)->setYPos(objList->at(0)->getYPos() - 0.01f);
					b2Vec2 vel = obj.at(objList->at(i))->GetLinearVelocity();
					vel.x = 0.0f;
					vel.y = -0.5f;
					obj.at(objList->at(i))->SetLinearVelocity(vel);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
					NewObject();
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Rest) {
					b2Vec2 vel = obj.at(objList->at(i))->GetLinearVelocity();
					vel.x = 0.0f;
					vel.y = 0.0f;
					obj.at(objList->at(i))->SetLinearVelocity(vel);
				}


				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


