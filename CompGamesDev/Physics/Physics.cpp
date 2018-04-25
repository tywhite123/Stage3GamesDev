#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects, EventQueue* eq) : objList(&objects)
{

	eQueue = eq;


	//world.SetContactListener(&contactListener);





	/*b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -12.6f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);*/



	for (auto ob : objects) {

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door) {
			ob->setHP(100);
		}

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
			
		if(ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door)
			dynamicBox.SetAsBox(ob->getScale().x/2, ob->getScale().y/2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() > ob->getYPos())
			dynamicBox.SetAsBox((ob->getScale().x / 2), ob->getScale().y / 2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() < ob->getYPos())
			dynamicBox.SetAsBox(ob->getScale().x / 2, (ob->getScale().y / 2));
		
			
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		fixtureDef.density = 1.0f;

		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		obj.insert(std::pair<GameObject*, b2Body*>(ob, body));
	}

}


Physics::~Physics()
{
}

void Physics::PhysicsUpdate(float msec)
{
	RecieveEvent();
	world.Step(timeStep, velocityIterations, positionIterations);

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
		
		
		//printf("%4.2f %4.2f %4.2f\n", o.first->getXPos(), o.first->getYPos(), angle);
		//printf("Enum Val: %d, Health: %d\n", o.first->getType(), o.first->getHP());
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

						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
							for (int z = 0; z < objList->size(); ++z) {

								

								
								for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
									if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
										if (contact->GetFixtureB()->GetBody() == obj.at(objList->at(z))) {
											objList->at(z)->updateHP(-1);
											
										}
										
									}
								}

								if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
 									if (objList->at(z)->getHP() <= 0) {
										world.DestroyBody(obj.at(objList->at(z)));
										obj.erase(objList->at(z));
										continue;
									}
								}

								//eQueue->pushEvent(new Event(GameEnums::MType::Update_Pos_AI));
							}
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


