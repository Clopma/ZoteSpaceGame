#pragma once

#include <entt.hpp>
#include "Core.h"
#include "Components.h"
#include "Rendering/Window.h"
#include "Event.h"
#include "Systems/ScriptSystem.h"
#include "Systems/MeshSystem.h"

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

	public:
		Scene() {}
		
		Scene(Window& window);

		void OnRenderFrame(OnRenderFrameArgs args);
		
		Entity& GetMainCamera() { return *mainCamera; }

		Scene(const Scene& other) {};

		Entity CreateEntity();
		~Scene();

	private:
		Renderer* renderer = nullptr;
		entt::registry registry;
		Entity* mainCamera = nullptr;

		Ref<ScriptSystem> m_scriptSystem;
		Ref<MeshSystem> m_meshSystem;

		void DrawLights();
	};
}