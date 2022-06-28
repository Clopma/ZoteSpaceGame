#pragma once

#include "Core.h"

#include <box2d/b2_world.h>

#include "ECS/Components/Rigidbody2DComponent.h"
#include "ECS/Components/TransformComponent.h"

#include "Utils/Memory.h"

namespace Zote
{
	class Scene;

	class ZOTE_API Physics2dSystem
	{
	private:
		Ref<b2World> m_world;
		Scene* m_scene = nullptr;
		float m_timeStep = 1.f / 60.f;
		int32 m_velocityIterations = 6;
		int32 m_positionIterations = 2;

		void UpdateFixture(Rigidbody2DComponent& rb);
		void UpdateBodyDef(Rigidbody2DComponent& rb, TransformComponent& transform);

	public:
		Physics2dSystem(Scene* scene);
		void Handle2dPhysics();
	};
}
