#pragma once
#include <nclgl\Window.h>
#include "Renderer.h"
#include <map>

class Graphics
{
public:
	Graphics(Window &parent, vector<GameObject*>& objects);
	~Graphics();

	void GraphicsUpdate(float msec);
	void NewObject();


	//bool CheckEsc() {
		//Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE);
	//}


	//Window getWindow() { return w; }

private:
	//Window w;
	Renderer r;

	Mesh* m;
	Shader* s;

	std::map<RenderObject*, GameObject*> obj;
	std::vector<GameObject*>* objList;

	float msec;
};

