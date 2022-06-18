#include "Texture.h"

namespace Zote
{
	Texture::Texture(std::string fileLoc)
		: fileLoc(fileLoc) {}
	
	void Texture::Load()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		stbi_set_flip_vertically_on_load(1);
		unsigned char* textureData = stbi_load
			(fileLoc.c_str(), &width, &height, &bitDepth, 0);
		if (!textureData)
		{
			LOG("Failed to find:" << "fileLoc");
			return;
		}
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		if (0 == bitDepth || 4 < bitDepth) { throw std::runtime_error("invalid depth"); }

		/*GLenum const fmt[] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
		GLenum const intFmt[] = {GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F};
		glTexImage2D(
			GL_TEXTURE_2D, 0, intFmt[bitDepth - 1],
			width, height, 0,
			fmt[bitDepth - 1], GL_UNSIGNED_BYTE, textureData);*/

		//glGenerateMipmap(GL_TEXTURE_2D);

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
