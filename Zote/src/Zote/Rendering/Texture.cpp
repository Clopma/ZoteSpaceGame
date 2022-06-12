#include "Texture.h"

namespace Zote
{
	Texture::Texture(std::string fileLoc)
		: fileLoc(fileLoc) {}
	
	void Texture::Load()
	{
		unsigned char* textureData = stbi_load
			(fileLoc.c_str(), &width, &height, &bitDepth, 0);
		if (!textureData)
		{
			LOG("Failed to find:" << "fileLoc");
			return;
		}
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, textureData);*/

		if (0 == bitDepth || 4 < bitDepth) { throw std::runtime_error("invalid depth"); }
		GLenum const fmt[] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
		glTexImage2D(
			GL_TEXTURE_2D, 0, fmt[bitDepth - 1],
			width, height, 0,
			fmt[bitDepth - 1], GL_UNSIGNED_BYTE, textureData);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(textureData);
	}
	void Texture::Use()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	void Texture::Clear()
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
		fileLoc = "";
	}
	Texture::~Texture()
	{
		Clear();
	}
}
