#pragma once
#include "Core.h"
#include <glew.h>
#include "Maths/GlmCommon.h"
#include <memory>
#include "Shader.h"

namespace Zote
{
	class ZOTE_API Line
	{
	public:

		std::shared_ptr<Shader> shader;
		Line() {}
		Line(vec3 start, vec3 end);
		void Use();
		~Line();

	private:
		
		float vertices[6];

		unsigned int VAO = 0;
		unsigned int VBO = 0;
		
	};
}