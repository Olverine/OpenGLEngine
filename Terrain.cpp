#include "Terrain.h"
#include "Engine.h"
#include <vector>

Terrain::~Terrain()
{
}

Vertex* Terrain::createFromBmp(char* filename)
{
	printf("Generating terrain from file: %s\n\n", filename);
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

											   // extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	int size = width * height;
	unsigned char* data = new unsigned char[size * 3]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size * 3, f); // read the rest of the data at once
	fclose(f);

	Vertex* vertices = new Vertex[size];
	//std::vector<Vertex> vertices;
	//vertices.reserve(size);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) {
			vertices[y * width + x].setPos(x, data[y * width * 3 + (x*3)], y);
			vertices[y * width + x].setUV(x,y);
			//vertices.push_back(Vertex(glm::vec3(x, data[y * width * 3 + (x * 3)], y), glm::vec2(x, y)));
			if (x > 0 && y > 0) {
				indices.push_back(y * width + x);
				indices.push_back(y * width + x-1);
				indices.push_back((y-1) * width + x - 1);

				indices.push_back((y-1) * width + x - 1);
				indices.push_back((y - 1) * width + x);
				indices.push_back(y * width + x);
			}
		}
	}

	return &vertices[0];
}

void Terrain::draw(glm::mat4 view, glm::mat4 projection) {
	glBindVertexArray(vertexArrayObject);

	shader->bind();
	shader->setMvp(projection * view * gameObject->getModel());

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);

	//glDrawArrays(GL_TRIANGLES, 0, width*height*4);

	glBindVertexArray(0);
}