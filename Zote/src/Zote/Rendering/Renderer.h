#pragma once

#include <glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Utils/Math.h"
#include "Utils/CustomTypes.h"
#include "Utils/Memory.h"

namespace Zote
{
	class Entity;

	class ZOTE_API Renderer
	{

	public:
		static void SetUniformMatrix(const cstr uniformName, Ref<Shader> shader, const mat4& matrix);
		static void DrawTriangles(const Ref<VertexArray> vertexArray, const Ref<IndexBuffer> indexBuffer, const Ref<Shader> shader);
		static void DrawLines(const Ref<VertexArray> vertexArray, const Ref<Shader> shader);
	};
}
