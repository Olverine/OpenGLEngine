#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <glm.hpp>
#include <GL/glew.h>

class Vertex{
public:
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
	}
private:
	glm::vec3 pos;
};

class Mesh : public Component
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void draw(glm::mat4 view, glm::mat4 projection);
	void setShader(Shader* newShader);
	Shader* getShader();
private:
	Shader* shader;

	enum {
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;
};
