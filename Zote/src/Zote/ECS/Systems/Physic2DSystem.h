#pragma once

#include "Core.h"

#include <box2d/b2_world.h>

#include "ECS/Components/PBody2DComponent.h"
#include "ECS/Components/TransformComponent.h"

#include "Utils/Memory.h"
#include "Utils/Math.h"

namespace Zote
{
	class Scene;

	class ZOTE_API Physic2DSystem
	{
	private:
		Ref<b2World> m_world;
		Scene* m_scene = nullptr;
		float m_timeStep = 1.f / 120.f;
		int32 m_velocityIterations = 6;
		int32 m_positionIterations = 2;
		float m_rotationOffset = .01f;

		void UpdateFixture(PBody2DComponent& rb);
		void UpdateBodyDef(PBody2DComponent& rb, TransformComponent& transform);

	public:
		vec2 m_worldGravity = { 0.f, -10.f };
		Physic2DSystem(Scene* scene);
		void Handle2dPhysics();
	};
}
