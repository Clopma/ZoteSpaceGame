#pragma once
#include "Core.h"

namespace Zote
{
	class Scene;

	class ZOTE_API MeshSystem
	{
		Scene* m_scene = nullptr;

	public:

		MeshSystem(Scene* scene);
		void HandleMeshes();
	};
}
