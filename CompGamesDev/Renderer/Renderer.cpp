#include "Renderer.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent)
{
	glEnable(GL_DEPTH_TEST);

	init = true;
}

Renderer::~Renderer(void)
{
}

void Renderer::RenderScene()
{

	//Render the scene and call render for each render objec
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
	SwapBuffers();
}

void Renderer::Render(const RenderObject & o)
{
	//Change the model matrix
	modelMatrix = o.GetWorldTransform();

	//Get shader and mesh
	if (o.GetShader() && o.GetMesh()) {
		/*SetCurrentShader(o.GetShader());*/
		currentShader = o.GetShader();
		GLuint program = o.GetShader()->GetProgram();
		glUseProgram(program);
		UpdateShaderMatrices();

		//Draw
		o.Draw();

		glUseProgram(0);


	}

	//Do for any child objects
	for (vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().begin(); ++i) //Implement if using this for parent/child probably use SceneNode
	{
		Render(*(*i));
	}
}

void Renderer::UpdateScene(float msec)
{

	//Update the scene
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		(*i)->Update(msec);
		
		//(*i)->SetModelMatrix(Matrix4::Translation(Vector3(obj.at(*i)->getXPos(), obj.at(*i)->getYPos(), (*i)->GetModelMatrix().GetPositionVector().z)));
	}
}
