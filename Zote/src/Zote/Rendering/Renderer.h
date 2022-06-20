#pragma once
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/LightComponent.h"
#include "ECS/Components/SpriteComponent.h"

#include "Utils/Math.h"
#include "Utils/CustomTypes.h"
#include "Utils/Memory.h"
#include "Utils/GlobalUniforms.h"

namespace Zote
{
	class Entity;

	class ZOTE_API Renderer
	{
		Entity* mainCamera = nullptr;

		void ApplyMatrixes(Ref<Shader> shader, TransformComponent& transform);

	public:

		Renderer() {}

		Renderer(Entity* mainCamera);		

		void DrawMesh(Ref<Mesh> mesh, Ref<Shader> shader, Ref<Texture> texture, TransformComponent& transform);
		void DrawLine(Ref<Line> line, Ref<Shader> shader, TransformComponent& transform);
		void DrawLight(MeshComponent& mesh, LightComponent& light);
	};
}
