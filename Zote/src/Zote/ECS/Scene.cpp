#include "Scene.h"
#include "Entity.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		mainCamera = new Entity();
		*mainCamera = CreateEntity();
		mainCamera->AddComponent<CameraComponent>();

		renderer = new Renderer(mainCamera->GetTransform(), mainCamera->GetComponent<CameraComponent>());
		
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
			renderer->DrawMesh(mesh, transform, args.aspect);
		}		
	}
	Entity Scene::CreateEntity()
	{
		return { registry.create(), this };
	}
	Scene::~Scene()
	{
		delete renderer;
		delete mainCamera;
	}
}