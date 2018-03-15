#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics(Window &w, vector<GameObject*>& objects, EventQueue* eq) : r(w), objList(&objects)
{
	m = Mesh::GenerateTriangle();
	s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

	eQueue = eq;

	if (!s->LinkProgram()) {
		return;
	}

	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(objects[0]->getXPos(), objects[0]->getYPos(), -10)) * Matrix4::Scale(Vector3(1.0f,1.0f,1.0f)));
	//RenderObject o2(m, s);
	//o.SetModelMatrix
	r.AddRenderObject(*o);
	//r.AddRenderObject(o2);

	//obj.insert(pair<RenderObject*, GameObject*>(o, objects[0]));

	r.AddObject(*o, *objects[0]);

	//r.SetProjMatrix(Matrix4::Orthographic(-10, 10, 10, 10, 10, 10));
	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	//r.SetProjMatrix(Matrix4::Orthographic(1, 1000, 10, -20, 10, -20));
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
	r.AddObject(*o, *objList->at(objList->size() - 1));
}

void Graphics::RecieveEvent()
{
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {

			if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
					r.getRenderObj().at(0)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(0)->getXPos(), objList->at(0)->getYPos(), -10.0f)) * Matrix4::Rotation(90.0f, Vector3(0.0f, 0.0f, 1.0f)));
					objList->at(i)->setRotation(90.0f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
					r.getRenderObj().at(0)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(0)->getXPos(), objList->at(0)->getYPos(), -10.0f)) * Matrix4::Rotation(270.0f, Vector3(0.0f, 0.0f, 1.0f)));
					objList->at(i)->setRotation(270.0f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
					r.getRenderObj().at(0)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(0)->getXPos(), objList->at(0)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)));
					objList->at(i)->setRotation(0.0f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
					r.getRenderObj().at(0)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(0)->getXPos(), objList->at(0)->getYPos(), -10.0f)) * Matrix4::Rotation(180.0f, Vector3(0.0f, 0.0f, 1.0f)));
					objList->at(i)->setRotation(180.0f);
				}
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
					NewObject();
				}

				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->popEvent();
					return;
				}
			}

		}
	}
}


