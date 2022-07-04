#include "MeshSystem.h"

#include "ECS/Entity.h"
#include "ECS/Scene.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/CameraComponent.h"

#include "Rendering/Renderer.h"
#include "Rendering/Mesh.h"

namespace Zote
{
	MeshSystem::MeshSystem(Scene* scene)
		: m_scene(scene) {}

	void MeshSystem::HandleMeshes()
	{
		auto& camera = m_scene->GetMainCamera().GetComponent<CameraComponent>();
		auto& cameraTransform = m_scene->GetMainCamera().GetComponent<TransformComponent>();

		auto group = m_scene->registry.group<TransformComponent>(entt::get<MeshComponent>);

		for (auto entity : group)
		{
			auto& meshComponent = group.get<MeshComponent>(entity);
			auto& transformComponent = group.get<TransformComponent>(entity);

			if (!meshComponent.enabled)
				continue;

			meshComponent.texture->Use();

			meshComponent.mesh->Render(meshComponent.shader, 
				camera.GetProjection(), camera.GetView(cameraTransform), transformComponent.GetModel());
		}
	}
}