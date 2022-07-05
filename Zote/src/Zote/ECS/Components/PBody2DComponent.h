#pragma once

#include "Core.h"
#include "BaseComponent.h"

#include <entt.hpp>
#include "ECS/Systems/Physic2DSystem.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Zote
{
	struct Body { b2Body* data = nullptr;};
	struct Fixture { b2Fixture* data = nullptr; };

	struct ZOTE_API PBody2DComponent : public BaseComponent
	{
		friend class Physic2DSystem;
		friend class ScriptSystem;
		friend class Collision2DCheckSystem;
		friend class Box2DGizmoSystem;
		friend class PBodyManager;
		friend class Scene;

	public:

		PBody2DComponent() 
		{
			m_body = MakeRef<Body>();
			m_fixture = MakeRef<Fixture>();
		}
		PBody2DComponent(const PBody2DComponent& other) = default;
		~PBody2DComponent()
		{
			m_physicsSystem->CleanBody(m_body->data);
		}

		enum class Mode { kinematic, dynamic };
		enum class Shape { box, circle };

		float GetGScale() const { return m_gScale; }
		const Mode& GetMode() const { return m_mode; }
		const vec2& GetColliderSize() const { return m_colliderSize; }
		float GetDensity() const { return m_density; }
		float GetFriction() const { return m_friction; }
		bool IsTrigger() const { return m_isTrigger; }
		const Shape& GetShape() const { return m_shape; }
		float GetRadius() const { return m_radius; }

		void SetGScale(float newGScale)
		{
			if (m_gScale == newGScale)
				return;
			m_gScale = newGScale;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetMode(const Mode& newMode) 
		{
			if (m_mode == newMode)
				return;
			m_mode = newMode;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetColliderSize(const vec2& newSize) 
		{
			if (m_colliderSize == newSize)
				return;
			m_colliderSize = newSize; 
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetDensity(float newDensity)
		{
			if (m_density == newDensity)
				return;
			m_density = newDensity;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetFriction(float newFriction)
		{
			if (m_friction == newFriction)
				return;
			m_friction = newFriction;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetIsTrigger(bool isTrigger) 
		{
			if (m_isTrigger == isTrigger)
				return;
			m_isTrigger = isTrigger;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetShape(Shape newShape)
		{
			if (m_shape == newShape)
				return;
			m_shape = newShape;
			m_physicsSystem->UpdateBodyDef(entity);
		}
		void SetRadius(float newRadius) 
		{ 
			if (m_radius == newRadius)
				return;
			m_radius = newRadius;
			m_physicsSystem->UpdateBodyDef(entity);
		}

		void SetLinearVelocity(const vec2 velocity)
		{
			m_body->data->SetLinearVelocity({ velocity.x, velocity.y });
		}
		void SetAngularVelocity(float velocity)
		{
			m_body->data->SetAngularVelocity(velocity);
		}
		
		void ApplyForce(const vec2& force)
		{
			m_body->data->ApplyForceToCenter({ force.x, force.y }, true);
		}
		void ApplyTorque(float torque)
		{
			m_body->data->ApplyTorque(torque, true);
		}		
		void ApplyLinearImpulse(const vec2& impulse)
		{
			m_body->data->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
		}
		void ApplyAngularImpulse(float impulse)
		{
			m_body->data->ApplyAngularImpulse(impulse, true);
		}

	private:

		Mode m_mode = Mode::kinematic;
		Shape m_shape = Shape::box;

		float m_gScale = 1.f;
		vec2 m_colliderSize = { 1.f, 1.f };
		float m_density = 1.f;
		float m_friction = .3f;
		bool m_isTrigger = false;
		float m_radius = 0.5f;

		bool m_bodyUpdated = false;

		Ref<Body> m_body;
		Ref<Fixture> m_fixture;

		Ref<Physic2DSystem> m_physicsSystem;
		entt::entity entity;

		b2PolygonShape m_box;
		b2CircleShape m_circle;
	};
}
