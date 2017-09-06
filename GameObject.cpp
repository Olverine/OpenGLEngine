#include "GameObject.h"
#include "Mesh.h"
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <common.hpp>



GameObject::GameObject()
{
}

GameObject::GameObject(std::string name)
{
	this->name = name;
}


GameObject::~GameObject()
{
}

void GameObject::addComponent(Component* component)
{
	component->gameObject = this;
	components.push_back(component);
}

glm::mat4 GameObject::getModel()
{
	glm::quat objRot = glm::quat(glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
	return glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale) * toMat4(objRot);
}

glm::vec3 GameObject::getForward()
{
	glm::vec4 forward4 = getModel() * glm::vec4(0, 0, 1, 0);
	return glm::normalize(glm::vec3(forward4.x, forward4.y, forward4.z));
}

glm::vec3 GameObject::getRight()
{
	glm::vec4 forward4 = getModel() * glm::vec4(-1, 0, 0, 0);
	return glm::normalize(glm::vec3(forward4.x, forward4.y, forward4.z));
}

glm::vec3 GameObject::getUp()
{
	glm::vec4 up4 = getModel() * glm::vec4(0, -1, 0, 0);
	return glm::normalize(glm::vec3(up4.x, up4.y, up4.z));
}

void GameObject::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}