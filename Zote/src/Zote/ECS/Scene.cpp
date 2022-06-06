#include "Scene.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		mainCamTransform = new Transform();
		mainCam = new Camera();

		//Main Camera setup
		entt::entity mainCamEntity = registry.create();

		Transform& tref = registry.emplace<Transform>(mainCamEntity);
		Camera& cref = registry.emplace<Camera>(mainCamEntity);

		*mainCamTransform = tref;
		*mainCam = cref;

		Renderer::currentCamera = mainCam;
		Renderer::currentCameraTransform = mainCamTransform;

		//Test triangle setup
		entt::entity testTriangle = registry.create();
		Transform& t = registry.emplace<Transform>(testTriangle);
		//t.position.z = 0.0f;
		MeshRenderer& meshRenderer = registry.emplace<MeshRenderer>(testTriangle);
		
		//Suscribe to DrawMesh to WindowUpdate
		window.OnRender.AddListener(new Zote::Delegate<OnRenderArgs>(this, &Scene::RenderEntities));
	}

	void Scene::RenderEntities(OnRenderArgs args)
	{
		auto group = registry.group<Transform>(entt::get<MeshRenderer>);
		//auto view = registry.view<MeshRenderer>();

		for (auto entity : group)
		{
			MeshRenderer& mesh = group.get<MeshRenderer>(entity);
			Transform& transform = group.get<Transform>(entity);
			Renderer::DrawMesh(mesh, transform, args.aspect);
		}		
	}
}