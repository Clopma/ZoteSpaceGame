#pragma once

#include "Core.h"

#include <entt.hpp>
#include <box2d/b2_world.h>

#include "Utils/Memory.h"
#include "Utils/Math.h"

namespace Zote
{
	class Scene;

	class ZOTE_API Physic2DSystem
	{
		friend class Scene;
		friend class PBody2DComponent;

	private:
		Ref<b2World> m_world;

		Scene* m_scene = nullptr;
		int m_frameRate = 120;
		int32 m_velocityIterations = 6;
		int32 m_positionIterations = 2;
		float m_rotationOffset = .01f;

		void UpdateFixture(entt::entity entity);
		void UpdateBodyDef(entt::entity entity);

		void Handle2dPhysics();

	public:
		vec2 m_worldGravity = { 0.f, -10.f };
		Physic2DSystem(Scene* scene);
	};
}
