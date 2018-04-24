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

	eQueue = eq;
	
	

	for (auto ob : objects) {

		if(ob->getType() == ObjectType::Map || ob->getType() == ObjectType::Wall)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"TexturedFragment.glsl");
	
		if (!s->LinkProgram()) {
			return;
		}

		if (ob->getShape() == "Square")
			m = Mesh::GenerateSquare(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		else if (ob->getShape() == "Quad")
			m = Mesh::GenerateQuad();

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

	
	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	
	
	
	
	//r.SetProjMatrix(Matrix4::Orthographic(1, 1000, 10, -20, 10, -20));
	//r.SetProjMatrix(Matrix4::Orthographic(-10, 10, 10, 10, 10, 10));
	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 5), Vector3(0, 0, -10)));


	

}

Graphics::~Graphics()
{
}

void Graphics::GraphicsUpdate(float msec)
{

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
	for (int i = eQueue->getEvents().size()-1; i >= 0; --i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {
			for (int o = 0; o < objList->size(); ++o) {


				if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {

					if (objList->at(o)->getType() == ObjectType::Player) {
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(90.0f);
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

						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
							for (int z = 0; z < objList->size(); ++z) {

								if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
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

				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


