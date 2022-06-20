#pragma once

#include <entt.hpp>
#include "Core.h"

#include "Rendering/Window.h"

#include "Event.h"

#include "Systems/ScriptSystem.h"
#include "Systems/MeshSystem.h"
#include "Systems/SpriteSystem.h"

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
		friend class LightSystem;
		friend class SpriteSystem;

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
	};
}