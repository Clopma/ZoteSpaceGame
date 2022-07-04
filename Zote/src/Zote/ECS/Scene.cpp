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
		m_transformGizmoSystem = MakeRef<TransformGizmoSystem>(this);
		m_Physic2DSystem = MakeRef<Physic2DSystem>(this);
		m_CollisionCheckSystem = MakeRef<Collision2DCheckSystem>(this);
		m_Box2DGizmoSystem = MakeRef<Box2DGizmoSystem>(this);

		window->OnRenderFrame.AddListener(new Delegate<OnRenderFrameArgs>(this, &Scene::OnRenderFrame));
	}

	void Scene::OnRenderFrame(OnRenderFrameArgs args)
	{
		m_Physic2DSystem->Handle2dPhysics();
//#ifdef ZOTE_DEBUG
		m_transformGizmoSystem->HandleGizmos();
//#endif	
		m_meshSystem->HandleMeshes();
		m_spriteSystem->HandleSprites();
		m_scriptSystem->HandleScripts(args.deltaTime);
		m_CollisionCheckSystem->Check2DCollisions();
//#ifdef ZOTE_DEBUG
		m_Box2DGizmoSystem->HandleBox2DGizmos();
//#endif	
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