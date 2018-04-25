#include "Renderer.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent)
{
	glEnable(GL_DEPTH_TEST);


	gltInit();
	playerHealth = gltCreateText();
	enemyHealth = gltCreateText();

	gltColor(1.0f, 1.0f, 1.0f, 1.0f);

	init = true;
}

Renderer::~Renderer(void)
{

	gltDeleteText(playerHealth);
	gltDeleteText(enemyHealth);
	gltTerminate();
}

void Renderer::RenderScene()
{

	//Render the scene and call render for each render objec
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}

	for (auto o : obj) {
		if (o.first->getType() == ObjectType::Player) {
			std::string health = "Player Health: " + std::to_string(o.first->getHP());

			gltSetText(playerHealth, health.c_str());
			gltDrawText2D(playerHealth, 0.0f, 0.0f, 1.0f);
		}
		else if (o.first->getType() == ObjectType::Enemy) {
			std::string health = "Enemy Health: " + std::to_string(o.first->getHP());
			gltSetText(enemyHealth, health.c_str());
			gltDrawText2D(enemyHealth, 0.0f, 15.0f, 1.0f);
		}
	}

	//gltDrawText2D(text, 0.0f, 0.0f, 1.0f);
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
