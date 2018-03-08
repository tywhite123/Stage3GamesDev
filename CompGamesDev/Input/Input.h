#pragma once

#include <nclgl\Window.h>
#include <Common\GameObject.h>
#include <Common\EventQueue.h>
#include "Controller.h"
#include "Gamepad.h"

class Input
{
public:
	Input(Window &w, std::vector<GameObject*>& objects, EventQueue* eq);
	~Input();

	void InputUpdate(float msec);

	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Input; }

protected:
	Window* win;
	EventQueue* eQueue;
	std::vector<GameObject*>* obj;
	Controller* con;
	Gamepad g;
};

