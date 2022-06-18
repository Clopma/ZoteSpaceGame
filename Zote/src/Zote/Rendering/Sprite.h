#pragma once
#include "Core.h"
#include <glew.h>

namespace Zote
{
	class ZOTE_API Sprite
	{
		using uint = unsigned int;
		using cstr = const char*;

		uint VAO = 0;
		uint VBO = 0;
		uint IBO = 0;
		uint indexCount = 0;

		const uint verticesCount = 12;
		const uint indicesCount = 6;

	public:

		const cstr GetVertPath() const 
			{ return "Sprites/spriteShader.vert"; }

		const cstr GetFragPath() const
			{ return "Sprites/spriteShader.frag"; }

		Sprite();
		void Render();
		void Clear();
		~Sprite();
	};
}