#include "Renderer.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent)
{
	glEnable(GL_DEPTH_TEST);
	//currentShader = new Shader(SHADERDIR"BasicVert.glsl", SHADERDIR"BasicFrag.glsl");
}

Renderer::~Renderer(void)
{
}

void Renderer::RenderScene()
{
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
}

void Renderer::Render(const RenderObject & o)
{
	modelMatrix = o.GetWorldTransform();

	if (o.GetShader() && o.GetMesh()) {
		GLuint program = o.GetShader()->GetProgram();
		glUseProgram(program);

		o.Draw();
	}

	for (vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().begin(); ++i) //Implement if using this for parent/child probably use SceneNode
	{
		Render(*(*i));
	}
}

void Renderer::UpdateScene(float msec)
{
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		(*i)->Update(msec);
	}
}
