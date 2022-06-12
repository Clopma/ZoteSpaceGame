#pragma once
#include "Core.h"
#include <glew.h>
#include <stb_image.h>
#include <string>
#include <iostream>

#define LOG(a) std::cout << a << std::endl;

namespace Zote
{
	class ZOTE_API Texture
	{

	public:

		Texture() {}
		Texture(std::string fileLoc);

		void Load();
		void Use();
		void Clear();

		~Texture();

	private:
		unsigned int textureID = 0;
		int width = 0;
		int	height = 0;
		int bitDepth = 0;
		std::string fileLoc;
	};
}

