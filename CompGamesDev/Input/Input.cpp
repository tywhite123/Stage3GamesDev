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
	g.Refresh();


	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W) || g.IsPressed(XINPUT_GAMEPAD_DPAD_UP)) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Up));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S) || g.IsPressed(XINPUT_GAMEPAD_DPAD_DOWN)) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Down));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A) || g.IsPressed(XINPUT_GAMEPAD_DPAD_LEFT)) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D) || g.IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_T)) {
	}

	

	if (g.IsPressed(XINPUT_GAMEPAD_A)) { 
		printf("Button A is pressed!\n");
	}

}