#pragma once

#include <nclgl\Window.h>
#include "Renderer.h"

class Graphics
{
public:
	Graphics(Window &parent);
	~Graphics();

	void GraphicsUpdate(float msec);

	//bool CheckEsc() {
		//Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE);
	//}


	//Window getWindow() { return w; }

private:
	//Window w;
	Renderer r;

	Mesh* m;
	Shader* s;

	float msec;
};

