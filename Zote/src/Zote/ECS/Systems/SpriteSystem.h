#pragma once
#include "Core.h"

namespace Zote
{
	class Scene;

	class ZOTE_API SpriteSystem
	{
		Scene* m_scene = nullptr;

	public:
		SpriteSystem(Scene* scene);
		void HandleSprites();
	};
}