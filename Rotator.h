#pragma once
#include "GameObject.h"
class Rotator :
	public Component
{
public:
	Rotator();
	~Rotator();

	glm::vec3 rotation;

	void update(float deltaTime);
};

