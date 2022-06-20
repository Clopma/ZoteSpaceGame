#pragma once
#include "Core.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	class Scene;

	class ZOTE_API LightSystem
	{
		Scene* m_scene = nullptr;

	public:

		LightSystem(Scene* scene);
		void HandleLights();
	};
}