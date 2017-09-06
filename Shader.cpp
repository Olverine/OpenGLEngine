#include "Shader.h"
#include "Engine.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

static std::string loadShader(const char* filename);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, char* errorMessage, const std::string& successMessage);
static GLuint createShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& dir)
{
	std::cout << "Compiling shader: " << dir << std::endl;

	program = glCreateProgram();
	std::cout << "Vert: ";
	shaders[0] = createShader(loadShader((dir + "/vert.glsl").c_str()), GL_VERTEX_SHADER);
	std::cout << "Frag: ";
	shaders[1] = createShader(loadShader((dir + "/frag.glsl").c_str()), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");

	std::cout << "Linking program: ";
	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "ERROR: Program failed to link", "done!");

	std::cout << "Validating program: ";
	glValidateProgram(program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "ERROR: Invalid shader program", "OK!");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "mvp");
	uniforms[COLOR_U] = glGetUniformLocation(program, "color");

	std::cout << std::endl;
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

static GLuint createShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		printError("ERROR: Shader createion failed");
	}

	const GLchar* source[1];
	GLint sourceLengths[1];
	source[0] = text.c_str();
	sourceLengths[0] = text.length();

	glShaderSource(shader, 1, source, sourceLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: Shader failed to compile", "compiled!");

	return shader;
}

void Shader::bind() {
	glUseProgram(program);
}

GLuint Shader::getId()
{
	return program;
}

void Shader::setMvp(glm::mat4 mvp) {
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &mvp[0][0]);
}

void Shader::setColor(glm::vec3 color) {
	glUniform3fv(uniforms[COLOR_U], 1, &color[0]);
}

static std::string loadShader(const char* filename) {
	std::ifstream file;
	file.open(filename);

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		printError(strcat("Unable to load shader: ", filename));
	}

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, char* errorMessage, const std::string& successMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		printError(error);
	}
	else {
		printSuccess(successMessage.c_str());
	}
}