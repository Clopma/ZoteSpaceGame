#pragma once
#include "Core.h"
#include "Maths/Color.h"
#include "Rendering/Shader.h"

#include <glew.h>
#include <glm/glm.hpp>

namespace Zote
{
	class ZOTE_API Light
	{
	public:
		Color m_color = { 1, 1, 1, 1 };
		float m_intensity = 1;

		const c_str m_colorUniformName = "directionalLight.color";
		const c_str m_intensityUniformName = "directionalLight.intensity";

		Light() {}
		Light(Color color, float intensity);

		void Use(const std::shared_ptr<Shader> shader);
	};
}