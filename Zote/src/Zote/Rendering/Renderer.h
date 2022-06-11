#pragma once

#include "ECS/Components.h"
#include <memory>
#include "Maths/GlmCommon.h"
#include <glm/gtc/type_ptr.hpp>

#include "ECS/Entity.h"

namespace Zote
{
	class ZOTE_API Renderer
	{
		Entity* mainCamera = nullptr;

		mat4 model = mat4(1.0);
		mat4 view = mat4(1.0);
		mat4 projection = mat4(1.0);

		void CalculateModel(TransformComponent& t);

		void UpdateCameraAxis();

		void CalculateProjection(float aspectRatio);

		void CalculateView();

		float* GetProjection() { return glm::value_ptr(projection); }
		float* GetView() { return glm::value_ptr(view); }
		float* GetModel() { return glm::value_ptr(model); }

	public:

		Renderer() {}

		Renderer(Entity* mainCamera);

		void DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio);
	};
}
