#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics(Window &w, vector<GameObject*>& objects, EventQueue* eq) : r(w), objList(&objects)
{
	/*m = Mesh::GenerateSquare(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	

	m->SetTexture(SOIL_load_OGL_texture("..\\TestLevel\\goomba.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!m->GetTexture()) {
		return;
	}*/

	//Set the event queue
	eQueue = eq;
	
	
	//For each game object create a render object
	for (auto ob : objects) {

		//Check the type of object and change shader based on that
		if(ob->getType() == ObjectType::Map || ob->getType() == ObjectType::Wall)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"TexturedFragment.glsl");
	
		if (!s->LinkProgram()) {
			return;
		}

		//Get the shape type and generate the correct mesh
		if (ob->getShape() == "Square")
			m = Mesh::GenerateSquare(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		else if (ob->getShape() == "Quad")
			m = Mesh::GenerateQuad();

		//Check for a texture and apply it if so
		if (ob->getTexPath() != "Null") {
			m->SetTexture(SOIL_load_OGL_texture(ob->getTexPath().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

			if (!m->GetTexture()) {
				return;
			}
			tex = true;
		}
		else {
			m->SetTexture(NULL);
			tex = false;
		}


		//Crete the render object and set position
		RenderObject* o = new RenderObject(m, s);
		o->SetModelMatrix(Matrix4::Translation(ob->getPos()) * Matrix4::Scale(Vector3(ob->getScale().x, ob->getScale().y, ob->getScale().x)));
		r.AddRenderObject(*o);
		r.AddObject(*ob, *o);

			
	}

	//RenderObject* o = new RenderObject(m, s);
	//o->SetModelMatrix(Matrix4::Translation(Vector3(objects[0]->getXPos(), objects[0]->getYPos(), -10)) * Matrix4::Scale(Vector3(0.25f,0.5f,0.5f)));
	////RenderObject o2(m, s);
	////o.SetModelMatrix
	//r.AddRenderObject(*o);
	////r.AddRenderObject(o2);

	////obj.insert(pair<RenderObject*, GameObject*>(o, objects[0]));

	//r.AddObject(*o, *objects[0]);

	//o = new RenderObject(Mesh::GenerateQuad(), s);
	//o->SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -50))* Matrix4::Scale(Vector3(20, 20, 20)));
	//r.AddRenderObject(*o);

	//o = new RenderObject(m, s);
	//o->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(objList->size() - 1)->getXPos(), objList->at(objList->size() - 1)->getYPos(), -10)) * Matrix4::Scale(Vector3(0.25f, 0.5f, 0.5f)));
	//r.AddRenderObject(*o);
	//r.AddObject(*o, *objList->at(objList->size() - 1));

	//Set the projection matrix
	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	
	
	
	
	//r.SetProjMatrix(Matrix4::Orthographic(1, 1000, 10, -20, 10, -20));
	//r.SetProjMatrix(Matrix4::Orthographic(-10, 10, 10, 10, 10, 10));
	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 5), Vector3(0, 0, -10)));


	

}

Graphics::~Graphics()
{
	for (auto o : obj) {
		delete o.second;
		o.second = nullptr;
	}
	delete m, s;
}

void Graphics::GraphicsUpdate(float msec)
{
	//Update
	RecieveEvent();
	r.UpdateScene(msec);
	r.RenderScene();
}

void Graphics::NewObject()
{
	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(objList->size()-1)->getXPos(), objList->at(objList->size() - 1)->getYPos(), -5)) * Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	r.AddRenderObject(*o);
	r.AddObject(*objList->at(objList->size() - 1), *o);
}

void Graphics::RecieveEvent()
{
	//For each event check the subsystems
	for (int i = eQueue->getEvents().size()-1; i >= 0; --i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {
			for (int o = 0; o < objList->size(); ++o) {

				//if the subsystem is graphics
				if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {

					//Check if the player is the object type
					if (objList->at(o)->getType() == ObjectType::Player) {

						//Handle movement of render object
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(90.0f);

							//Check for scale for animation
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(270.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(0.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(180.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
						}

						//Check if atteck
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
							for (int z = 0; z < objList->size(); ++z) {

								//Check object type is the enemy or door
								if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
									
									//get its current hp and delete if it is dead
									if (objList->at(z)->getHP() <= 0) {
										r.removeRenderObj(objList->at(z));
										objList->erase(objList->begin() + z);
										
										continue;
									}
								}
							}
						}

					}


					if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
						NewObject();
					}

					//If it is an enemy update its pos based on if its pushed
					if (objList->at(o)->getType() == ObjectType::Enemy) {
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Update_Pos_AI) {
							/*r.getRenderObj().at(1)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(1)->getXPos(), objList->at(1)->getYPos(), -10.0f)));*/
							pushed = true;
						}

						if (pushed) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Scale(Vector3(0.25f, 0.5f, 0.5f)));
						}
					}
				}


				//pop event
				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


