#include "Mesh.h"
#include "Input.h"
#include <iostream>
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++) {
		positions.push_back(vertices[i].getPosition());
		texCoords.push_back(vertices[i].getTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);

	//Position buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[UV_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw(glm::mat4 view, glm::mat4 projection) {
	glBindVertexArray(vertexArrayObject);

	shader->bind();
	shader->setMvp(projection * view * gameObject->getModel());

	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}

void Mesh::setShader(Shader* newShader)
{
	shader = newShader;
}

Shader* Mesh::getShader()
{
	return shader;
}
