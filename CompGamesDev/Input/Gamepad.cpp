#include "Gamepad.h"
#include <stdio.h>
#include <math.h>


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

		//Left stick code see - https://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx
		LX = state.Gamepad.sThumbLX;
		LY = state.Gamepad.sThumbLY;

		float mag = sqrt(LX*LX + LY*LY);

		float normalisedLX = LX / mag;
		float normalisedLY = LY / mag;

		float normalisedMag = 0;

		if (mag > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {

			if (mag > 32767) mag = 32767;

			mag -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			normalisedMag = mag / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		}
		else {
			mag = 0.0;
			normalisedMag = 0.0;
		}

		//Code for controller vibration
		/*XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = 65535; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
		XInputSetState(0, &vibration);*/

		//printf("Left Stick LX: %f\nLeft Stick LY: %f\nMagnitude: %f\n", normalisedLX, normalisedLY, normalisedMag);
		//printf("Left Stick LX: %f\nLeft Stick LY: %f\nMagnitude: %f\n", LX, LY, mag);

		

		return true;
	}
	return false;
}
