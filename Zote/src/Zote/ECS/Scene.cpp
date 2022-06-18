#include "Scene.h"
#include "Entity.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		m_scriptSystem = MakeRef<ScriptSystem>(this);

		mainCamera = new Entity();
		*mainCamera = CreateEntity();
		mainCamera->AddComponent<CameraComponent>();
		renderer = new Renderer(mainCamera);
		//Suscribe to DrawMesh to WindowUpdate
		window.OnRenderFrame.AddListener(new Delegate<OnRenderFrameArgs>(this, &Scene::OnRenderFrame));
	}

	void Scene::OnRenderFrame(OnRenderFrameArgs args)
	{
		DrawMeshes(args);
		DrawLights();
		m_scriptSystem->HandleScripts(args.deltaTime);
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
	void Scene::DrawMeshes(OnRenderFrameArgs args)
	{
		auto group = registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			MeshComponent& mesh = group.get<MeshComponent>(entity);
			TransformComponent& transform = group.get<TransformComponent>(entity);
			renderer->DrawMesh(mesh, transform, args.aspect);
		}
	}
	void Scene::DrawLights()
	{
		auto lightView = registry.view<LightComponent>();
		auto meshView = registry.view<MeshComponent>();

		for (auto lightEntity : lightView)
		{
			auto& light = lightView.get<LightComponent>(lightEntity);

			for (auto meshEntity : meshView)
			{
				auto& mesh = meshView.get<MeshComponent>(meshEntity);
				renderer->DrawLight(mesh, light);
			}
		}
	}
}