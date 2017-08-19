#include "Mesh.h"
#include "Input.h"
#include <iostream>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
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
