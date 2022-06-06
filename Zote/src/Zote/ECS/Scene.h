#pragma once
#include <entt.hpp>
#include "Core.h"
#include "Components.h"
#include "Rendering/Window.h"
#include "Event.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	class ZOTE_API Scene
	{

	public:
		Scene() {}
		Scene(Window& window);
		void RenderEntities(OnRenderArgs args);

		Scene(const Scene& other) {};
	
	private:
		entt::registry registry;
	};
}

