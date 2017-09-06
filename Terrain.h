#pragma once
#include "Mesh.h"
class Terrain :
	public Mesh
{
public:
	Terrain(char* fileName) {

		Vertex* vertices = createFromBmp(fileName);

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, width * height * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}
	~Terrain();

	void draw(glm::mat4 view, glm::mat4 projection);

private:
	Vertex* createFromBmp(char*);
	int width;
	int height;
	std::vector<unsigned int> indices;
	GLuint elementbuffer;
};

