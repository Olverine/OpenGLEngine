#include "GameObject.h"
#include "Mesh.h"



GameObject::GameObject()
{
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
	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotXMat = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotYMat = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZMat = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotationMat = rotZMat * rotXMat * rotYMat;
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
	return translationMat * rotationMat * scaleMat;
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