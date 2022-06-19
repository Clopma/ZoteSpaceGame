#pragma once
#include "Core.h"
#include <glew.h>

#include "VertexArray.h"
#include "VertexBuffer.h";
#include "IndexBuffer.h";

#include "Utils/CustomTypes.h";
#include "Utils/Memory.h"

namespace Zote
{
	class ZOTE_API Sprite
	{
	public:

		cstr GetVertPath() const { return "Shaders/spriteShader.vert"; }
		cstr GetFragPath() const { return "Shaders/spriteShader.frag"; }

		Sprite();
		void Render();

	private:
		Ref<VertexArray> m_vertexArray;
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<IndexBuffer> m_indexBuffer;

		const uint verticesCount = 16;
		const uint indicesCount = 6;
	};
}