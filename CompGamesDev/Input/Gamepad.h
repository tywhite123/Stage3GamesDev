#pragma once
#include <windows.h>
#include <Xinput.h>
#include "Controller.h"

class Gamepad : public Controller
{
public:
	Gamepad();
	~Gamepad();

	bool IsPressed(WORD button);
	bool CheckConnected();
	bool Refresh();

protected:
	XINPUT_STATE state;
	int controllerID;
};

