#pragma once

#include "GameObject.h"

class CameraFly : public Component
{
public:
	CameraFly();
	~CameraFly();

	void update(float);

	float velocity = 10.0f;
	float sensitivity = 100.0;

	int controllerId = 0;

private:
	float angleHor = 0;
	float angleVert = 0;
};

