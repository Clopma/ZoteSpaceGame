#include "Scene.h"
#include "Entity.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	Scene::Scene(Window& window)
	{
		mainCamera = new Entity();
		*mainCamera = CreateEntity();
		mainCamera->AddComponent<CameraComponent>();
		renderer = new Renderer(mainCamera);

		m_scriptSystem = MakeRef<ScriptSystem>(this);
		m_meshSystem = MakeRef<MeshSystem>(this, renderer);

		window.OnRenderFrame.AddListener(new Delegate<OnRenderFrameArgs>(this, &Scene::OnRenderFrame));
	}

	void Scene::OnRenderFrame(OnRenderFrameArgs args)
	{
		m_meshSystem->HandleMeshes(args.aspect);
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