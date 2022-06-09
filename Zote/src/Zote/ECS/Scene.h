#pragma once

#include <entt.hpp>
#include "Core.h"
#include "Components.h"
#include "Rendering/Window.h"
#include "Event.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	class Entity;

	class ZOTE_API Scene
	{
		friend class Entity;

	public:
		Scene() {}
		Scene(Window& window);
		void OnRenderFrame(OnRenderFrameArgs args);

		Scene(const Scene& other) {};

		Entity CreateEntity();
		~Scene();

	private:
		Renderer* renderer = nullptr;
		entt::registry registry;
		Entity* mainCamera = nullptr;
		glm::vec3 defaultCameraPos = { 0.0f, 0.0f, 2.5f };
	};
}