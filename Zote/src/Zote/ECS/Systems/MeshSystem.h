#pragma once
#include "Core.h"
#include "Rendering/Renderer.h"

namespace Zote
{
	class Scene;

	class ZOTE_API MeshSystem
	{
		Scene* m_scene = nullptr;
		Renderer* m_renderer = nullptr;

	public:

		MeshSystem(Scene* scene, Renderer* renderer);
		void HandleMeshes(float aspectRatio);
	};
}
