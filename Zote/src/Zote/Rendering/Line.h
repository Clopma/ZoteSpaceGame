#pragma once
#include "Core.h"
#include <glew.h>
#include "Shader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"

#include "Utils/CustomTypes.h"
#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Zote
{
	class ZOTE_API Line
	{
	public:
		
		Line(vec3 start, vec3 end, Color color);
		void Render(Ref<Shader> shader);

		cstr GetVertShaderPath() const { return "Shaders/lineShader.vert"; }
		cstr GetFragShaderPath() const { return "Shaders/lineShader.frag"; }

	private:

		Ref<VertexArray> m_vertexArray;
		Ref<VertexBuffer> m_vertexBuffer;
		Color m_color = Color::red;
		cstr m_uniformColorName = "color";
		const uint m_lineCount = 6;
	};
}