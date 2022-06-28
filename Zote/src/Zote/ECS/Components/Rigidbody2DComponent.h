#pragma once

#include "Core.h"
#include "BaseComponent.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "Utils/Math.h"

namespace Zote
{
	struct ZOTE_API Rigidbody2DComponent : public BaseComponent
	{
		friend class Physics2dSystem;
	public:

		Rigidbody2DComponent() {}
		Rigidbody2DComponent(const Rigidbody2DComponent& other) = default;

		enum class Mode { kinematic, dynamic };

		float GetGScale() const { return m_gScale; }
		const Mode& GetMode() const { return m_mode; }
		const vec2& GetColliderSize() const { return m_colliderSize; }
		float GetDensity() const { return m_density; }
		float GetFriction() const { return m_friction; }

		void SetGScale(float newGScale)
		{
			if (m_gScale == newGScale)
				return;
			m_bodyUpdated = false;
			m_gScale = newGScale;
		}
		void SetMode(const Mode& newMode) 
		{
			if (m_mode == newMode)
				return;
			m_bodyUpdated = false;
			m_mode = newMode; 
		}
		void SetColliderSize(const vec2& newSize) 
		{
			if (m_colliderSize == newSize)
				return;
			m_bodyUpdated = false; 
			m_colliderSize = newSize; 
		}
		void SetDensity(float newDensity)
		{
			if (m_density == newDensity)
				return;
			m_fixtureUpdated = false;
			m_density = newDensity;
		}
		void SetFriction(float newFriction)
		{
			if (m_friction == newFriction)
				return;
			m_fixtureUpdated = false;
			m_friction = newFriction;
		}

	private:

		Mode m_mode = Mode::kinematic;
		float m_gScale = 1.f;
		vec2 m_colliderSize = { 1.f, 1.f };
		float m_density = 1.f;
		float m_friction = .3f;

		bool m_bodyUpdated = false;
		bool m_fixtureUpdated = false;

		b2Body* m_body = nullptr;
		b2Fixture* m_fixture = nullptr;
		
		b2PolygonShape m_box;
	};
}
