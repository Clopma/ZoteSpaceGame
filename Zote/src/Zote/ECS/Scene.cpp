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
		window.OnRenderFrame.AddListener(new Zote::Delegate<OnRenderFrameArgs>(this, &Scene::OnRenderFrame));
	}

	void Scene::OnRenderFrame(OnRenderFrameArgs args)
	{
		auto group = registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			MeshComponent& mesh = group.get<MeshComponent>(entity);
			TransformComponent& transform = group.get<TransformComponent>(entity);
			renderer->DrawMesh(mesh, transform, args.aspect);
		}

		auto view = registry.view<ScriptComponent>();
		for (auto entity : view)
		{
			ScriptComponent& scriptComponent = view.get<ScriptComponent>(entity);
			
			if (!scriptComponent.enabled) 
				return;

			for (auto script : scriptComponent.scripts)
			{
				if ((!script->enabled))
					continue;

				if (!script->started)
				{
					script->Start();
					script->started = true;
				}

				script->Update(args.deltaTime);
			}
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