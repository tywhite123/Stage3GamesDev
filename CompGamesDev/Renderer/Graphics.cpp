#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics(Window &w) :/* w("CSC3224 - Game Engine", 1920, 1080),*/ r(w)
{
	m = Mesh::GenerateTriangle();
	s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

	

	if (!s->LinkProgram()) {
		return;
	}

	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -5)) * Matrix4::Scale(Vector3(1,1,1)));
	//RenderObject o2(m, s);
	//o.SetModelMatrix
	r.AddRenderObject(*o);
	//r.AddRenderObject(o2);

	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 5), Vector3(0, 0, -10)));

	/*while (true) {
		r.UpdateScene(msec);
		r.RenderScene();
	}*/

	

}

Graphics::~Graphics()
{
}

void Graphics::GraphicsUpdate(float msec)
{
	//msec = w.GetTimer()->GetTimedMS();
	//r.RenderScene();
	r.UpdateScene(msec);
	r.RenderScene();
	//r.SwapBuffers();
}
