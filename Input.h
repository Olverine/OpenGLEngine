#pragma once

#include "Engine.h"

#include <Xinput.h>

namespace Input {
	void update();
	bool isConnected(int);
	float getLeftStickX(int);
	float getLeftStickY(int);
	float getRightStickX(int);
	float getRightStickY(int);
	bool getButton(int, DWORD);
	glm::vec2 getMouseDelta();
}
