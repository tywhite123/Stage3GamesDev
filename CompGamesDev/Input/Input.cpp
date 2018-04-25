#include "Input.h"

Input::Input(Window & w, std::vector<GameObject*>& objects, EventQueue* eq)
{
	win = &w;
	obj = &objects;
	eQueue = eq;

	//Create the controller objects
	g = new Gamepad();
	kb = new KeyboardController();

	//Check to see if gamepad is connected before deciding what controller to use
	if (g->CheckConnected()) {
		con = g;
	}
	else {
		con = kb;
	}
	
}

Input::~Input()
{
	delete kb, g;
	con = g = kb = nullptr;
}

void Input::InputUpdate(float msec)
{
	//Refresh the gamepad
	g->Refresh();

	//Check if the gamepad is connected to and change controller accordingly
	if (g->CheckConnected()) {
		con = g;
	}
	else {
		con = kb;
	}

	//Calls the control functions based on what the controller is
	if (con->up()) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Up));
	}

	else if (con->down()) {
		//obj->at(0)->setYPos(obj->at(0)->getYPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Down));
	}

	else if (con->left()) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() - 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}

	else if (con->right()) {
		//obj->at(0)->setXPos(obj->at(0)->getXPos() + 0.1f);
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}
	else {
		eQueue->pushEvent(new Event(GameEnums::MType::Rest));
	}

	if (con->attack()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Attack));
	}

}