#include "Input.h"
#include <iostream>
#include <string>
#include <sstream>

bool prevConnectionStates[4];
bool connectionStates[4];
XINPUT_STATE prevGamepadStates[4];
XINPUT_STATE gamepadStates[4];

DWORD buttonStates[4];
float jlx[4];
float jly[4];
float jrx[4];
float jry[4];
float tl[4];
float tr[4];

void Input::update()
{
	DWORD dwResult;
	for (DWORD i = 0; i< XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&prevGamepadStates, sizeof(XINPUT_STATE) * 4);

		for (int i = 0; i < 4; i++) {
			prevGamepadStates[i] = gamepadStates[i];
			prevConnectionStates[i] = connectionStates[i];
		}

		ZeroMemory(&gamepadStates, sizeof(XINPUT_STATE) * 4);

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &gamepadStates[i]);

		if (dwResult == ERROR_SUCCESS)
		{
			connectionStates[i] = true;
			if(!prevConnectionStates[i]){
				std::ostringstream msg;
				msg << "Gamepad " << (i + 1) << " connected";
				printSuccess(msg.str().c_str());

				/*XINPUT_VIBRATION vibration;
				memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
				vibration.wLeftMotorSpeed = (int)(65535.0f);
				XInputSetState(i, &vibration);*/
			}

			buttonStates[i] = gamepadStates[i].Gamepad.wButtons;
			jlx[i] = gamepadStates[i].Gamepad.sThumbLX;
			jly[i] = gamepadStates[i].Gamepad.sThumbLY;
			jrx[i] = gamepadStates[i].Gamepad.sThumbRX;
			jry[i] = gamepadStates[i].Gamepad.sThumbRY;
		}
		else
		{
			connectionStates[i] = false;
			if (prevConnectionStates[i]) {
				std::ostringstream msg;
				msg << "Gamepad " << (i + 1) << " disconnected";
				printColored(msg.str().c_str(), ERROR_COLOR);
			}
		}
	}
}

bool Input::isConnected(int id) {
	return connectionStates[id];
}

float Input::getLeftStickX(int id)
{
	if (abs(jlx[id]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return jlx[id] / (32768 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ;
	}
	else {
		return 0;
	}
}

float Input::getLeftStickY(int id)
{
	if (abs(jly[id]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return jly[id] / (32768 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else {
		return 0;
	}
}

float Input::getRightStickX(int id)
{
	if (abs(jrx[id]) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		return jrx[id] / (32768 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	}
	else {
		return 0;
	}
}

float Input::getRightStickY(int id)
{
	if (abs(jry[id]) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		return jry[id] / (32768 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	}
	else {
		return 0;
	}
}

bool Input::getButton(int id, DWORD button)
{
	return (buttonStates[id] & button) == button;
}
