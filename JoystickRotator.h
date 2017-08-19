#pragma once
#include "Rotator.h"
#include "Input.h"
class JoystickRotator :
	public Rotator
{
public:
	JoystickRotator();
	~JoystickRotator();
	void update(float deltaTime);
};

