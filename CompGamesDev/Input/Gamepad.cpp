#include "Gamepad.h"
#include <stdio.h>


Gamepad::Gamepad()
{
}


Gamepad::~Gamepad()
{
}

bool Gamepad::IsPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
}

bool Gamepad::CheckConnected()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &state);
		if(dwResult == ERROR_SUCCESS){
			printf("Controller Connected in port %d", i);
			controllerID = i;
		}
		else{
		}
	}
	return controllerID != -1;
}

bool Gamepad::Refresh()
{
	if (controllerID == -1) {
		CheckConnected();
	}
	if (controllerID != -1) {
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(controllerID, &state) != ERROR_SUCCESS) {
			controllerID = -1;
			return false;
		}
		return true;
	}
	return false;
}
