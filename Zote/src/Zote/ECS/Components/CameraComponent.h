#pragma once
#include "Core.h"
#include "BaseComponent.h"

#include "Utils/Math.h"

namespace Zote
{
	struct ZOTE_API CameraComponent : public BaseComponent
	{
		enum class Mode { Perspective, Ortographic };

		Mode mode = Mode::Ortographic;

		float fov = 45.f;
		float near = 0.1f;
		float far = 100.0f;

		vec2 size = { 2.f, 2.f };

		CameraComponent() {}

		CameraComponent(const CameraComponent& other) = default;
	};
}