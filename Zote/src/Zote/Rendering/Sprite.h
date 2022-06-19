#pragma once
#include "Core.h"
#include <glew.h>

#include "VertexBuffer.h";
#include "IndexBuffer.h";

#include "Utils/CustomTypes.h";
#include "Utils/Memory.h"

namespace Zote
{
	class ZOTE_API Sprite
	{
		uint VAO = 0;

		Ref<VertexBuffer> vb;
		Ref<IndexBuffer> ib;

		const uint verticesCount = 16;
		const uint indicesCount = 6;

	public:

		const cstr GetVertPath() const 
			{ return "Shaders/spriteShader.vert"; }

		const cstr GetFragPath() const
			{ return "Shaders/spriteShader.frag"; }

		Sprite();
		void Render();
		~Sprite();
	};
}