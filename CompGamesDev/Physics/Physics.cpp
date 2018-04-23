#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects, EventQueue* eq) : objList(&objects)
{

	eQueue = eq;


	///world.SetContactListener(&contactListener);





	/*b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -12.6f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);*/



	for (auto ob : objects) {

		if (ob->getType() == ObjectType::Map) {
			continue;
		}

		b2BodyDef bodyDef;

		if (ob->getType() == ObjectType::Player) {
			bodyDef.type = b2_dynamicBody;
		}
		if (ob->getType() == ObjectType::Enemy) {
			bodyDef.type = b2_staticBody;
		}
		if (ob->getType() == ObjectType::Wall || ob->getType() == ObjectType::Door) {
			bodyDef.type = b2_staticBody;
		}


		bodyDef.position.Set(ob->getXPos(), ob->getYPos());
		b2Body* body = world.CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy) {
			dynamicBox.SetAsBox(0.125f, 0.25f);
		}

		else if (ob->getType() == ObjectType::Wall && ob->getXPos() > ob->getYPos()) 
			dynamicBox.SetAsBox(4.0f, 16.13f);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() < ob->getYPos()){
			//bodyDef.position.Set(ob->getXPos(), ob->getYPos()/5);
			dynamicBox.SetAsBox(16.13f, 4.0f);
		}
		/*else if(ob->getType() == ObjectType::Wall && )*/
			
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		fixtureDef.density = 1.0f;

		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		obj.insert(std::pair<GameObject*, b2Body*>(ob, body));
	}




	/*b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(objects[0]->getXPos(), objects[0]->getYPos());
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.015625f, 0.125f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	obj.insert(std::pair<GameObject*, b2Body*>(objects[0], body));*/






	/*GameObject* o = new GameObject(1.0f, 1.0f);
	objList->push_back(o);
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_dynamicBody;
	bodyDef2.position.Set(o->getXPos(), o->getYPos());
	b2Body* body2 = world.CreateBody(&bodyDef2);

	b2PolygonShape dynamicBox2;
	dynamicBox2.SetAsBox(0.015625f, 0.125f);

	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &dynamicBox;

	fixtureDef2.density = 1.0f;

	fixtureDef2.friction = 0.0f;

	body2->CreateFixture(&fixtureDef2);

	obj.insert(std::pair<GameObject*, b2Body*>(objList->at(objList->size() - 1), body2));*/

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
	for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {		
		contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		contact->GetFixtureA()->GetBody()->SetAngularVelocity(0);
		contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

		//eQueue->pushEvent(new Event(GameEnums::MType::Update_Pos_AI));
	}

	b2Vec2 pos;

	for (auto o : obj) {
		b2Vec2 position = o.second->GetPosition();
		pos = position;
		float32 angle = o.second->GetAngle();

		o.first->setXPos(position.x);
		o.first->setYPos(position.y);
		
		
		/*for (b2ContactEdge* edge = o.second->GetContactList(); edge; edge = edge->next) {
			b2Vec2 pos = edge->contact->GetFixtureB()->GetBody()->GetPosition();
			printf("%4.2f, %4.2f\n", pos.x, pos.y);
		}*/
		
		printf("%4.2f %4.2f %4.2f\n", o.first->getXPos(), o.first->getYPos(), angle);
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
			for (int o = 0; o < objList->size(); ++o) {

				if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {

					if (objList->at(o)->getType() == ObjectType::Player) {
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
							//objList->at(0)->setXPos(objList->at(0)->getXPos() - 0.01f);
							b2Vec2 vel = obj.at(objList->at(0))->GetLinearVelocity();
							vel.x = -0.5f;
							vel.y = 0.0f;
							obj.at(objList->at(0))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
							///objList->at(0)->setXPos(objList->at(0)->getXPos() + 0.01f);
							b2Vec2 vel = obj.at(objList->at(0))->GetLinearVelocity();
							vel.x = 0.5f;
							vel.y = 0.0f;
							obj.at(objList->at(0))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
							//objList->at(0)->setYPos(objList->at(0)->getYPos() + 0.01f);
							b2Vec2 vel = obj.at(objList->at(0))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = 0.5f;
							obj.at(objList->at(0))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
							//objList->at(0)->setYPos(objList->at(0)->getYPos() - 0.01f);
							b2Vec2 vel = obj.at(objList->at(0))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = -0.5f;
							obj.at(objList->at(0))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
							NewObject();
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Rest) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = 0.0f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}
					}
					
			}
			


				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j 
					&& eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


