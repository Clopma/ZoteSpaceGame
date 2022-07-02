#include "TransformGizmoSystem.h"

#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components/CameraComponent.h"

#include "Rendering/Renderer.h"


namespace Zote
{
	TransformGizmoSystem::TransformGizmoSystem(Scene* scene)
	: m_scene(scene) {}

	void TransformGizmoSystem::HandleGizmos()
	{
		auto view = m_scene->registry.view<TransformComponent>();
		auto& camera = m_scene->GetMainCamera().GetComponent<CameraComponent>();
		auto& cameraTransform = m_scene->GetMainCamera().GetComponent<TransformComponent>();

		for (auto entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);

			if (!GizmosExists(entity))
				gizmos.emplace_back(entity);

			DrawGizmosAxis(entity, camera.GetProjection(), camera.GetView(cameraTransform), transform.GetModel());
		}
	}

	bool TransformGizmoSystem::GizmosExists(const entt::entity& entity) const
	{
		for (auto gizmo : gizmos)
		{
			if (gizmo.m_entity == entity)
				return true;
		}

		return false;
	}

	void TransformGizmoSystem::DrawGizmosAxis(const entt::entity& entity, mat4 p, mat4 v, mat4 m) const
	{
		for (auto gizmo : gizmos)
		{
			if (gizmo.m_entity == entity)
				gizmo.DrawGizmosAxis(p, v, m);
		}
	}
}