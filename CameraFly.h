#pragma once

#include "GameObject.h"

class CameraFly : public Component
{
public:
	CameraFly();
	~CameraFly();

	void update(float);

	float velocity = 1.0f;
	float sensitivity = 1.0;
};

