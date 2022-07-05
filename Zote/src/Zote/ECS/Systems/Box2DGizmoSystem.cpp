#include "Box2DGizmoSystem.h"

#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/PBody2DComponent.h"
#include "ECS/Entity.h"

namespace Zote
{
	Box2DGizmoSystem::Box2DGizmoSystem(Scene* scene)
	: m_Scene(scene) {}
	
	void Box2DGizmoSystem::HandleBox2DGizmos()
	{
		auto view = m_Scene->registry.view<PBody2DComponent, TransformComponent>();
		auto& camera = m_Scene->GetMainCamera().GetComponent<CameraComponent>();
		auto& cameraTransform = m_Scene->GetMainCamera().GetComponent<TransformComponent>();

		for (auto entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);
			auto& pb = view.get<PBody2DComponent>(entity);

			if (pb.GetShape() != PBody2DComponent::Shape::box)
				continue;

			BoxGizmo* gizmo = FindGizmo(entity);

			if (gizmo == nullptr)
				gizmo = &m_BoxGizmos.emplace_back(pb.GetColliderSize(), entity);

			gizmo->Render(camera.GetProjection(), camera.GetView(cameraTransform), transform.GetModel());
		}
	}

	BoxGizmo* Box2DGizmoSystem::FindGizmo(const entt::entity& entity)
	{
		for (auto& gizmo : m_BoxGizmos)
		{
			if (gizmo.m_Entity == entity)
				return &gizmo;
		}
		return nullptr;
	}
}