#include "TerrainShader.h"


TerrainShader::~TerrainShader()
{
}

void TerrainShader::update(float deltaTime) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grassTextureId);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cliffTextureId); 

	setGrassUniform(0);
	setCliffUniform(1);
}

void TerrainShader::getUniforms()
{
	uniforms[GRASS_U] = glGetUniformLocation(program, "grass");
	uniforms[CLIFF_U] = glGetUniformLocation(program, "cliff");
}

void TerrainShader::setGrassUniform(GLint grassTexture)
{
	glUniform1i(uniforms[GRASS_U], grassTexture);
}

void TerrainShader::setCliffUniform(GLint cliffTexture)
{
	glUniform1i(uniforms[CLIFF_U], cliffTexture);
}
