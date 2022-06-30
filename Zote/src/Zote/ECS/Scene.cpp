#include "Scene.h"
#include "Entity.h"
#include "Components/CameraComponent.h"

namespace Zote
{
	Scene::Scene(Ref<Window> window)
	{
		mainCamera = new Entity();
		*mainCamera = CreateEntity();
		mainCamera->AddComponent<CameraComponent>(window);

		m_scriptSystem = MakeRef<ScriptSystem>(this);
		m_meshSystem = MakeRef<MeshSystem>(this);
		m_spriteSystem = MakeRef<SpriteSystem>(this);
		m_gizmosAxisSystem = MakeRef<GizmosAxisSystem>(this);
		m_physics2dSystem = MakeRef<Physics2dSystem>(this);

		window->OnRenderFrame.AddListener(new Delegate<OnRenderFrameArgs>(this, &Scene::OnRenderFrame));
	}

	void Scene::OnRenderFrame(OnRenderFrameArgs args)
	{
		m_physics2dSystem->Handle2dPhysics();
		m_gizmosAxisSystem->HandleGizmosAxis();
		m_meshSystem->HandleMeshes();
		m_spriteSystem->HandleSprites();
		m_scriptSystem->HandleScripts(args.deltaTime);
	}

	Entity Scene::CreateEntity()
	{
		return { registry.create(), this };
	}
	Scene::~Scene()
	{
		delete mainCamera;
	}
}