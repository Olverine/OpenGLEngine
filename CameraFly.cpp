#include "CameraFly.h"

#include "Input.h"

CameraFly::CameraFly()
{
}

CameraFly::~CameraFly()
{
}

void CameraFly::update(float deltaTime)
{
	float tempVelocity = velocity;
	if (Input::getButton(0, XINPUT_GAMEPAD_LEFT_THUMB)) {
		tempVelocity *=5;
	}
	gameObject->position += gameObject->getForward() * Input::getLeftStickY(0) * tempVelocity * deltaTime;
	gameObject->position += gameObject->getRight() * Input::getLeftStickX(0) * tempVelocity * deltaTime;
	angleVert -= Input::getRightStickY(0) * sensitivity * deltaTime;
	angleHor -=  Input::getRightStickX(0) * sensitivity * deltaTime;

	gameObject->rotation = glm::vec3(angleVert, angleHor, 0);
}
