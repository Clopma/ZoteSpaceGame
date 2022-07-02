#pragma once

namespace Zote
{
	class Scene;

	class Collision2DCheckSystem
	{
		Scene* m_scene = nullptr;

	public:

		Collision2DCheckSystem(Scene* scene);
		void Check2DCollisions();
	};
}
