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


	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W) || g.IsPressed(XINPUT_GAMEPAD_DPAD_UP) || g.getLY() >= 10000) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Up));
	}

	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_S) || g.IsPressed(XINPUT_GAMEPAD_DPAD_DOWN) || g.getLY() <= -10000) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Down));
	}

	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_A) || g.IsPressed(XINPUT_GAMEPAD_DPAD_LEFT) || g.getLX() <= -10000) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}

	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_D) || g.IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || g.getLX() >= 10000) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}
	else {
		eQueue->pushEvent(new Event(GameEnums::MType::Rest));
	}

	if (g.IsPressed(XINPUT_GAMEPAD_B)) {
		g.vibrate();
	}

	if (g.IsPressed(XINPUT_GAMEPAD_X) || Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		eQueue->pushEvent(new Event(GameEnums::MType::Attack));
	}

}