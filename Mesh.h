#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <glm.hpp>
#include <GL/glew.h>

class Vertex{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& uv) {
		this->pos = pos;
		this->uv = uv;
	}
	Vertex() {
		this->pos = glm::vec3(0);
		this->uv = glm::vec2(0);
	}

	void setPos(const glm::vec3& pos) {
		this->pos = pos;
	}
	void setPos(float x, float y, float z){
		this->pos = glm::vec3(x, y, z);
	}

	void setUV(const glm::vec2& uv) {
		this->uv = uv;
	}
	void setUV(float x, float y) {
		this->uv = glm::vec2(x, y);
	}

	glm::vec3 getPosition() {
		return pos;
	}

	glm::vec2 getTexCoord() {
		return uv;
	}
private:
	glm::vec3 pos;
	glm::vec2 uv;
};

class Mesh : public Component
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	Mesh();
	~Mesh();
	void draw(glm::mat4 view, glm::mat4 projection);
	void update(float deltaTime);
	void setShader(Shader* newShader);
	Shader* getShader();
protected:
	Shader* shader;

	enum {
		POSITION_VB,
		UV_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;
};
