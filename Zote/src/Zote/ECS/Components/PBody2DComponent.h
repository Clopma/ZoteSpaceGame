#pragma once

#include "Core.h"
#include "BaseComponent.h"

#include <entt.hpp>
#include "ECS/Systems/Physic2DSystem.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include "TagComponent.h"

#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Zote
{
	struct ZOTE_API PBody2DComponent : public BaseComponent
	{
		friend class Physic2DSystem;
		friend class ScriptSystem;
		friend class Collision2DCheckSystem;
		friend class Box2DGizmoSystem;
		friend class PBodyManager;
		friend class Scene;

	public:

		PBody2DComponent() {}
		
		PBody2DComponent(const PBody2DComponent& other)
		{
			m_mode = Mode::kinematic;
			m_shape = Shape::box;
			m_gScale = other.m_gScale;
			m_colliderSize = other.m_colliderSize;
			m_density = other.m_density;
			m_friction = other.m_friction;
			m_isTrigger = other.m_isTrigger;
			m_radius = other.m_radius;
			m_body = other.m_body;
			m_fixture = other.m_fixture;
			m_physicsSystem = other.m_physicsSystem;
			entity = other.entity;
			m_box = other.m_box;
			m_circle = other.m_circle;

			coping = true;
		}

		~PBody2DComponent()
		{
			if (coping) return;
			str name = GetEntity().GetComponent<TagComponent>().name;
			coping = false;
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
			m_body->SetLinearVelocity({ velocity.x, velocity.y });
		}
		void SetAngularVelocity(float velocity)
		{
			m_body->SetAngularVelocity(velocity);
		}
		
		void ApplyForce(const vec2& force)
		{
			m_body->ApplyForceToCenter({ force.x, force.y }, true);
		}
		void ApplyTorque(float torque)
		{
			m_body->ApplyTorque(torque, true);
		}		
		void ApplyLinearImpulse(const vec2& impulse)
		{
			m_body->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
		}
		void ApplyAngularImpulse(float impulse)
		{
			m_body->ApplyAngularImpulse(impulse, true);
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

		static constexpr auto in_place_delete = true;

		b2Body* m_body = nullptr;
		b2Fixture* m_fixture = nullptr;
		bool coping = false;

		Ref<Physic2DSystem> m_physicsSystem;
		entt::entity entity{0};

		b2PolygonShape m_box;
		b2CircleShape m_circle;
	};
}