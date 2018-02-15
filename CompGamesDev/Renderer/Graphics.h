#pragma once

#include <nclgl\Window.h>
#include "Renderer.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void GraphicsUpdate(/*float msec*/);

	bool CheckEsc() {
		Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE);
	}


	Window getWindow() { return w; }

private:
	Window w;
	Renderer r;

	float msec;
};

