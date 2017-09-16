#pragma once
#include "Shader.h"
class TerrainShader :
	public Shader
{
public:
	TerrainShader() : Shader("shaders/terrain") {};
	~TerrainShader();


	GLuint grassTextureId;
	GLuint cliffTextureId;

	void update(float deltaTime);

private:

	virtual void getUniforms();

	void setGrassUniform(GLint grassTexture);
	void setCliffUniform(GLint cliffTexture);

	enum {
		TRANSFORM_U,
		COLOR_U,
		GRASS_U,
		CLIFF_U,

		NUM_UNIFORMS
	};
};

