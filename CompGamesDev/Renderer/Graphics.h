#pragma once

#include <Common\MessageQueue.h>
#include <nclgl\Window.h>
#include "Renderer.h"
#include <map>

class Graphics
{
public:
	Graphics(Window &parent, vector<GameObject*>& objects, MessageQueue &queue);
	~Graphics();

	void GraphicsUpdate(float msec);
	void NewObject();
	void UpdateMessage();

	//bool CheckEsc() {
		//Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE);
	//}


	//Window getWindow() { return w; }

private:
	//Window w;
	Renderer r;

	Mesh* m;
	Shader* s;

	MessageQueue* mQueue;

	std::map<RenderObject*, GameObject*> obj;
	std::vector<GameObject*>* objList;

	float msec;
};

