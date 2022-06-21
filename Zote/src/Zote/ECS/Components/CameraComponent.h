#pragma once
#include "Core.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "Rendering/Window.h"

#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Zote
{
	struct ZOTE_API CameraComponent : public BaseComponent
	{
		enum class Mode { Perspective, Ortographic };

		Mode mode = Mode::Ortographic;

		float fov = 45.f;
		float near = 0.1f;
		float far = 100.0f;

		vec2 size = { 2.f, 1.5f };

		CameraComponent(Ref<Window> window)
			: m_window(window) {}

		CameraComponent(const CameraComponent& other) = default;

		const mat4& GetProjection() const
		{
			if (mode == CameraComponent::Mode::Ortographic)
				return glm::ortho(-size.x, size.x, -size.y, size.y, near, far);

			if (mode == CameraComponent::Mode::Perspective)
				return glm::perspective(fov, m_window->GetAspect(), near, far);
		}

		const mat4& GetView(TransformComponent& cameraTransform) const
		{
			return glm::lookAt(cameraTransform.GetPosition(), cameraTransform.GetPosition()
				+ cameraTransform.GetForward(), cameraTransform.GetUp());
		}

	private:
		Ref<Window> m_window;
	};
}