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
	Vertex(float x, float y, float z) {
		this->pos = glm::vec3(x,y,z);
	}
	Vertex() {
		this->pos = glm::vec3(0, 0, 0);
	}
	void setPos(const glm::vec3& pos) {
		this->pos = pos;
	}
	void setPos(float x, float y, float z){
		this->pos = glm::vec3(x, y, z);
	}
private:
	glm::vec3 pos;
};

class Mesh : public Component
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	Mesh();
	~Mesh();
	void draw(glm::mat4 view, glm::mat4 projection);
	void setShader(Shader* newShader);
	Shader* getShader();
protected:
	Shader* shader;

	enum {
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;
};
