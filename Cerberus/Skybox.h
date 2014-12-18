#ifndef SKYBOX_H
#define SKYBOX_H

#include "Material.h"

class Skybox : public BaseMaterial
{
public:
	Skybox();
	~Skybox();

	void destroy();
	void bind();
	void unbind();

	void loadCubeTexture(const std::string& filenamePosZ, const std::string filenameNegZ, const std::string& filenamePosX,
		const std::string& filenameNegX, const std::string& filenamePosY, const std::string& filenameNegY);

	GLuint getCubeTexture();
private:
	GLuint m_CubeTexture;


};

#endif