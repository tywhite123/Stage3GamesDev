#include "Input.h"

Input::Input(Window & w, std::vector<GameObject*>& objects)
{
	win = &w;
	obj = &objects;
}

Input::~Input()
{
}

void Input::InputUpdate(float msec)
{
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		obj->at(0)->setYPos(obj->at(0)->getYPos() + 0.1f);
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		obj->at(0)->setYPos(obj->at(0)->getYPos() - 0.1f);
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		obj->at(0)->setXPos(obj->at(0)->getXPos() - 0.1f);
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		obj->at(0)->setXPos(obj->at(0)->getXPos() + 0.1f);
	}
}