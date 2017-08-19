#include "Camera.h"
#include <iostream>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::render()
{
	for each (GameObject* obj in getObjects())
	{
		for each (Component* comp in obj->components)
		{
			comp->draw(getView(), getProjection());
		}
	}
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(gameObject->position, gameObject->position + gameObject->getForward(), gameObject->getUp());
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(fov, 4.0f / 3.0f, nearClip, farClip);
}
