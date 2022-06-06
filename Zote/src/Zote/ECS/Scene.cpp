#include "Scene.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		//Main Camera setup
		entt::entity mainCamEntity = registry.create();
		auto camT = registry.emplace<Transform>(mainCamEntity);
		Camera& mainCam = registry.emplace<Camera>(mainCamEntity);

		//Provide main camera to the renderer
		Renderer::currentCamera = &mainCam;
		Renderer::currentCameraTransform = &camT;

		//Test triangle setup
		entt::entity testTriangle = registry.create();
		Transform& t = registry.emplace<Transform>(testTriangle);
		t.position.z = 2.5f;
		registry.emplace<MeshRenderer>(testTriangle);
		
		//Suscribe to DrawMesh to WindowUpdate
		window.OnRender.AddListener(new Zote::Delegate<OnRenderArgs>(this, &Scene::RenderEntities));
	}

	void Scene::RenderEntities(OnRenderArgs args)
	{
		auto group = registry.group<Transform>(entt::get<MeshRenderer>);
		//auto view = registry.view<MeshRenderer>();

		for (auto entity : group)
		{
			auto mesh = group.get<MeshRenderer>(entity);
			auto transform = group.get<Transform>(entity);
			Renderer::DrawMesh(mesh, transform, args.aspect);
		}		
	}
}