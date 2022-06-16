#include "Light.h"

namespace Zote
{
	Light::Light(Color color, float intensity)
		: m_color(color), m_intensity(intensity) {}
	
	void Light::Use(const std::shared_ptr<Shader> shader)
	{
		shader->Use();

		int intensityLocation = shader->GetUniform(m_intensityUniformName);
		int colorLocation = shader->GetUniform(m_colorUniformName);

		glUniform1f(intensityLocation, m_intensity);
		glUniform3f(colorLocation, m_color.r, m_color.g, m_color.b);

		shader->Unbind();
	}
}