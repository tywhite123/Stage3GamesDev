#include "Input.h"

Input::Input(Window & w, std::vector<GameObject*>& objects, EventQueue* eq)
{
	win = &w;
	obj = &objects;
	eQueue = eq;
	
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
		//obj->at(0)->setXPos(obj->at(0)->getXPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_T)) {
	}

	g.Refresh();

	if (g.IsPressed(XINPUT_GAMEPAD_A)) { 
		printf("Button A is pressed!\n");
	}
	if (g.IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}
	if (g.IsPressed(XINPUT_GAMEPAD_DPAD_LEFT)) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}
}