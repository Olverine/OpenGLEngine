#pragma once
#include <string>
#include <GL/glew.h>
#include <glm.hpp>

class Shader
{
public:
	Shader(const std::string& dir);
	~Shader();

	void bind();
	GLuint getId();

	void setMvp(glm::mat4 mvp);
	void setColor(glm::vec3 color);

private:
	enum {
		TRANSFORM_U,
		COLOR_U,

		NUM_UNIFORMS
	};

	static const int NUM_SHADERS = 2;
	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

