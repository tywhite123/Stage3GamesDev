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

	float getLX() { return LX; }
	float getLY() { return LY; }

protected:
	XINPUT_STATE state;
	int controllerID;

	float LX;
	float LY;

};

