#include "JoystickRotator.h"
#include "Mesh.h"
#include <iostream>


JoystickRotator::JoystickRotator()
{
}


JoystickRotator::~JoystickRotator()
{
}

void JoystickRotator::update(float deltaTime) {
	float LX = Input::getLeftStickX(0);
	float LY = Input::getLeftStickY(0);
	rotation = glm::vec3(LY, LX, 0.0f);
	Mesh* mesh = gameObject->getComponent<Mesh>();
	mesh->getShader()->setColor(glm::vec3(LX - LY, LY, -LX - LY));
	Rotator::update(deltaTime);
}