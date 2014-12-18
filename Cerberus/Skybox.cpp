#include "Skybox.h"
#include "Texture.h"
#include "Vertex.h"

Skybox::Skybox()
{
	m_CubeTexture = 0;
}

Skybox::~Skybox()
{

}

void Skybox::destroy()
{
	if (m_CubeTexture)
	{
		glDeleteTextures(1, &m_CubeTexture);
	}
}

void Skybox::bind()
{
	glDepthMask(GL_FALSE);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture);

	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexPosLocation, "vertexPosition");

	glDisableVertexAttribArray(vertexPosLocation);
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

}

void Skybox::unbind()
{
	glDepthMask(GL_TRUE);
}

void Skybox::loadCubeTexture(const std::string& filenamePosZ, const std::string filenameNegZ, const std::string& filenamePosX,
	const std::string& filenameNegX, const std::string& filenamePosY, const std::string& filenameNegY)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_CubeTexture);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

	loadCubeMapSide(filenamePosZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	loadCubeMapSide(filenameNegZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	loadCubeMapSide(filenamePosZ, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	loadCubeMapSide(filenameNegZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	loadCubeMapSide(filenamePosY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	loadCubeMapSide(filenameNegY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);

}

GLuint Skybox::getCubeTexture()
{
	return m_CubeTexture;
}

