#pragma once
#include "Core.h"
#include "BaseComponent.h"
#include "Rendering/Lighting/Light.h"

#include "Utils/Memory.h"
#include "Utils/Math.h"

namespace Zote
{
	struct ZOTE_API LightComponent : public BaseComponent
	{
		friend class Renderer;

		const Color& GetColor() const { return light->m_color; }
		void SetColor(const Color& newColor) { light->m_color = newColor; }

		const float& GetIntensity() const { return light->m_intensity; }
		void SetIntensity(const float& newIntens) { light->m_intensity = newIntens; }

		LightComponent()
		{
			light = MakeRef<Light>();
		}
		LightComponent(const LightComponent& other) = default;

	private:
		Ref<Light> light;
	};
}
