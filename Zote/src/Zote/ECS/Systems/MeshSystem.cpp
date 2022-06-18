#include "MeshSystem.h"
#include "ECS/Scene.h"

namespace Zote
{
	MeshSystem::MeshSystem(Scene* scene, Renderer* renderer)
		: m_scene(scene), m_renderer(renderer) {}

	void MeshSystem::HandleMeshes(float aspectRatio)
	{
		auto group = m_scene->registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			MeshComponent& mesh = group.get<MeshComponent>(entity);
			TransformComponent& transform = group.get<TransformComponent>(entity);
			m_renderer->DrawMesh(mesh, transform, aspectRatio);
		}
	}
}