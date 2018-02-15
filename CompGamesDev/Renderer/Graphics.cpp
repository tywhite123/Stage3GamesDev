#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics() : w("CSC3224 - Game Engine", 1920, 1080), r(w)
{
	Mesh* m = Mesh::GenerateTriangle();
	Shader* s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

	if (!s->LinkProgram()) {
		return;
	}

	RenderObject o(m, s);
	//RenderObject o2(m, s);
	//o.SetModelMatrix
	r.AddRenderObject(o);
	//r.AddRenderObject(o2);

	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));

	/*while (true) {
		r.UpdateScene(msec);
		r.RenderScene();
	}*/

	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 5), Vector3(0, 0, -10)));

}

Graphics::~Graphics()
{
}

void Graphics::GraphicsUpdate(/*float msec*/)
{
	msec = w.GetTimer()->GetTimedMS();
	//r.RenderScene();
	r.UpdateScene(msec);
	r.RenderScene();
	r.SwapBuffers();
}
