#pragma once
#include "Core.h"
#include <glew.h>
#include "Maths/GlmCommon.h"
#include <memory>
#include "Shader.h"
#include "Maths/Color.h"

namespace Zote
{
	class ZOTE_API Line
	{
	public:

		const char* uniformColorName = "color";
		std::shared_ptr<Shader> shader;
		Line() {}
		Line(vec3 start, vec3 end, Color color);
		void Use();
		~Line();

	private:
		
		float vertices[6];
		Color color;
		unsigned int VAO = 0;
		unsigned int VBO = 0;
		
	};
}