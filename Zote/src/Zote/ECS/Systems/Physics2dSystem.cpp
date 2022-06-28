#include "Physics2dSystem.h"

#include <entt.hpp>


#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include <box2d/b2_math.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "ECS/Entity.h"
#include "ECS/Scene.h"

namespace Zote
{
	void Physics2dSystem::UpdateFixture(Rigidbody2DComponent& rb)
	{
		b2FixtureDef fixtureDef;

		fixtureDef.shape = &rb.m_box;
		fixtureDef.density = rb.m_density;
		fixtureDef.friction = rb.m_friction;

		if (rb.m_fixture != nullptr)
		{
			rb.m_body->DestroyFixture(rb.m_fixture);
			rb.m_fixture = nullptr;
		}

		rb.m_fixture = rb.m_body->CreateFixture(&fixtureDef);
		rb.m_fixtureUpdated = true;
	}

	void Physics2dSystem::UpdateBodyDef(Rigidbody2DComponent& rb, TransformComponent& transform)
	{
		b2BodyDef bodyDef;
		bodyDef.type = rb.m_mode == Rigidbody2DComponent::Mode::dynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(transform.GetPosition().x, transform.GetPosition().y);
		bodyDef.angle = glm::eulerAngles(transform.GetRotation()).z;
		bodyDef.gravityScale = rb.m_gScale;

		if (rb.m_body != nullptr)
		{
			m_world->DestroyBody(rb.m_body);
			rb.m_body = nullptr;
		}

		rb.m_body = m_world->CreateBody(&bodyDef);
		rb.m_box.SetAsBox(rb.m_colliderSize.x/2.f, rb.m_colliderSize.y/2.f);

		rb.m_bodyUpdated = true;
		UpdateFixture(rb);
	}

	Physics2dSystem::Physics2dSystem(Scene* scene)
		: m_scene(scene)
	{
		m_world = MakeRef<b2World>(b2Vec2(0.f, -10.f));
	}

	void Physics2dSystem::Handle2dPhysics()
	{
		auto view = m_scene->registry.view<Rigidbody2DComponent>();

		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

		for (auto entity : view)
		{
			auto& rb = view.get<Rigidbody2DComponent>(entity);
			auto& transform = rb.GetEntity()->GetComponent<TransformComponent>();
			
			if (!rb.m_bodyUpdated)
				UpdateBodyDef(rb, transform);

			else if (!rb.m_fixtureUpdated)
				UpdateFixture(rb);

			b2Vec2 position = rb.m_body->GetPosition();
			transform.SetPosition({ position.x, position.y, transform.GetPosition().z });
			
			float angle = rb.m_body->GetAngle();
			float selfAngle = glm::eulerAngles(transform.GetRotation()).z;
			
			float dif = std::abs(std::abs(angle) - std::abs(selfAngle));

			if (dif > 0.1f)
				transform.RotateGlobal(angle, { 0, 0, 1 });
		}
	}
}