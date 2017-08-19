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
	gameObject->position += gameObject->getForward() * Input::getLeftStickY(0) * velocity * deltaTime;
	gameObject->position += gameObject->getRight() * Input::getLeftStickX(0) * velocity * deltaTime;
	gameObject->rotation += glm::vec3(0,-1,0) * Input::getRightStickX(0) * sensitivity * deltaTime;
	gameObject->rotation += gameObject->getRight() * Input::getRightStickY(0) * sensitivity * deltaTime;
}
