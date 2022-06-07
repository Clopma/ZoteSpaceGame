#include "Scene.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		//Main Camera setup
		entt::entity mainCamEntity = registry.create();

		TransformComponent& tref = registry.emplace<TransformComponent>(mainCamEntity);
		CameraComponent& cref = registry.emplace<CameraComponent>(mainCamEntity);

		mainCam_Camera = std::make_shared<CameraComponent>(cref);
		mainCam_Transform = std::make_shared<TransformComponent>(tref);

		renderer = Renderer(mainCam_Camera, mainCam_Transform);

		//Test triangle setup
		entt::entity testTriangle = registry.create();
		TransformComponent& t = registry.emplace<TransformComponent>(testTriangle);
		t.position.z = -2.5f;
		t.position.y = 0.5f;
		MeshComponent& meshRenderer = registry.emplace<MeshComponent>(testTriangle);
		
		//Suscribe to DrawMesh to WindowUpdate
		window.OnRender.AddListener(new Zote::Delegate<OnRenderArgs>(this, &Scene::RenderEntities));
	}

	void Scene::RenderEntities(OnRenderArgs args)
	{
		auto group = registry.group<TransformComponent>(entt::get<MeshComponent>);
		//auto view = registry.view<MeshRenderer>();

		for (auto entity : group)
		{
			MeshComponent& mesh = group.get<MeshComponent>(entity);
			TransformComponent& transform = group.get<TransformComponent>(entity);
			renderer.DrawMesh(mesh, transform, args.aspect);
		}		
	}
}