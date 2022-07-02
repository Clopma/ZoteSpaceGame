#pragma once

#include <entt.hpp>
#include "Core.h"

#include "Rendering/Window.h"

#include "Event.h"

#include "Systems/ScriptSystem.h"
#include "Systems/MeshSystem.h"
#include "Systems/SpriteSystem.h"
#include "Systems/TransformGizmoSystem.h"
#include "Systems/Physic2DSystem.h"
#include "Systems/Collision2DCheckSystem.h"

#include "Utils/Memory.h"

namespace Zote
{
	class Entity;
	class Renderer;

	class ZOTE_API Scene
	{
		friend class Entity;
		friend class ScriptSystem;
		friend class MeshSystem;
		friend class SpriteSystem;
		friend class TransformGizmoSystem;
		friend class Physic2DSystem;
		friend class Collision2DCheckSystem;

	public:
		Scene() {}
		
		Scene(Ref<Window> window);

		void OnRenderFrame(OnRenderFrameArgs args);
		
		Entity& GetMainCamera() { return *mainCamera; }

		Scene(const Scene& other) {};

		Entity CreateEntity();
		~Scene();

	private:
		entt::registry registry;

		Entity* mainCamera = nullptr;

		Ref<ScriptSystem> m_scriptSystem;
		Ref<MeshSystem> m_meshSystem;
		Ref<SpriteSystem> m_spriteSystem;
		Ref<TransformGizmoSystem> m_transformGizmoSystem;
		Ref<Physic2DSystem> m_Physic2DSystem;
		Ref<Collision2DCheckSystem> m_CollisionCheckSystem;
	};
}