#pragma once

#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Mesh;

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void addComponent(Component*);

	template<class T>
	T * getComponent()
	{
		for each (T* component in components)
		{
			if (dynamic_cast<T*>(component) != 0) {
				return (dynamic_cast<T*>(component));
			}
		}
		return NULL;
	}

	glm::mat4 getModel();
	glm::vec3 getForward();
	glm::vec3 getRight();
	glm::vec3 getUp();

	void setPosition(float x, float y, float z);

	std::vector<Component*> components;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Component
{
public:
	virtual void init() {}
	virtual void update(float deltaTime) {}
	virtual void render() {}
	virtual void draw(glm::mat4 view, glm::mat4 projection) {}

	GameObject* gameObject;
};
