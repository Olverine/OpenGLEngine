#pragma once

#include "GameObject.h"
#include "Engine.h"

class Camera :
	public Component
{
public:
	Camera();
	~Camera();

	void render();

	float fov = 30.0f;

	float nearClip = 0.1f;
	float farClip = 2000.0f;

	glm::mat4 getView();
	glm::mat4 getProjection();
};

