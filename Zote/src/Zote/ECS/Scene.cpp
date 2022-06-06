#include "Scene.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		entt::entity entity = registry.create();
		
		registry.emplace<Transform>(entity);
		registry.emplace<MeshRenderer>(entity);
		window.OnRender.AddListener(new Zote::Delegate<OnRenderArgs>(this, &Scene::RenderEntities));
	}

	void Scene::RenderEntities(OnRenderArgs args)
	{
		auto group = registry.group<Transform>(entt::get<MeshRenderer>);

		for (auto entity : group)
		{
			//Transform& transform = group.get<Transform>(entity);
			MeshRenderer& meshRenderer = group.get<MeshRenderer>(entity);
			meshRenderer.mesh.Render();
		}
	}
}