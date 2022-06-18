#pragma once
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/LightComponent.h"

#include "Utils/Math.h"
#include "Utils/CustomTypes.h"

namespace Zote
{
	class Entity;

	class ZOTE_API Renderer
	{
		Entity* mainCamera = nullptr;

		mat4 model = mat4(1.0);
		mat4 view = mat4(1.0);
		mat4 projection = mat4(1.0);	

		cstr modelUniformName = "model";
		cstr viewUniformName = "view";
		cstr projectionUniformName = "projection";

		void CalculateModel(TransformComponent& t);
		void CalculateProjection(float aspectRatio);
		void CalculateView();

	public:

		Renderer() {}

		Renderer(Entity* mainCamera);

		void DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio);
		void DrawLight(MeshComponent& mesh, LightComponent& light);
	};
}
