#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics(Window &w, vector<GameObject*>& objects) : r(w), objList(&objects)
{
	m = Mesh::GenerateTriangle();
	s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

	

	if (!s->LinkProgram()) {
		return;
	}

	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(objects[0]->getXPos(), objects[0]->getYPos(), -5)) * Matrix4::Scale(Vector3(1,1,1)));
	//RenderObject o2(m, s);
	//o.SetModelMatrix
	r.AddRenderObject(*o);
	//r.AddRenderObject(o2);

	//obj.insert(pair<RenderObject*, GameObject*>(o, objects[0]));

	r.AddObject(*o, *objects[0]);

	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 5), Vector3(0, 0, -10)));


	

}

Graphics::~Graphics()
{
}

void Graphics::GraphicsUpdate(float msec)
{
	r.UpdateScene(msec);
	r.RenderScene();
}

void Graphics::NewObject()
{
	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(objList->size()-1)->getXPos(), objList->at(objList->size() - 1)->getYPos(), -5)) * Matrix4::Scale(Vector3(1, 1, 1)));
	r.AddRenderObject(*o);
	r.AddObject(*o, *objList->at(objList->size() - 1));
}


