#pragma once
#include "Mesh.h"
#include <vector>
class Terrain :
	public Mesh
{
public:
	Terrain(char* fileName) {

		Vertex* vertices = createFromBmp(fileName);

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;

		positions.reserve(width * height);
		texCoords.reserve(width * height);

		for (unsigned int i = 0; i < width * height; i++) {
			positions.push_back(vertices[i].getPosition());
			texCoords.push_back(vertices[i].getTexCoord());
		}

		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);

		// Position buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, width * height * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// UV buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[UV_VB]);
		glBufferData(GL_ARRAY_BUFFER, width * height * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

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

