#include "Physic2DSystem.h"


#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_body.h>

#include "ECS/Entity.h"
#include "ECS/Scene.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/PBody2DComponent.h"
#include "ECS/Components/TransformComponent.h"

namespace Zote
{
	void Physic2DSystem::UpdateFixture(entt::entity entity)
	{
		auto& rb = m_scene->registry.get<PBody2DComponent>(entity);

		b2FixtureDef fixtureDef;

		switch (rb.m_shape)
		{
		case PBody2DComponent::Shape::circle:
			fixtureDef.shape = &rb.m_circle;
			break;

		default: 
			fixtureDef.shape = &rb.m_box; 
			break;
		}

		fixtureDef.density = rb.m_density;
		fixtureDef.friction = rb.m_friction;
		fixtureDef.isSensor = rb.m_isTrigger;

		rb.m_fixture->data = rb.m_body->data->CreateFixture(&fixtureDef);
	}

	void Physic2DSystem::UpdateBodyDef(entt::entity entity)
	{
		auto& rb = m_scene->registry.get<PBody2DComponent>(entity);
		auto& transform = m_scene->registry.get<TransformComponent>(entity);

		b2BodyDef bodyDef;
		bodyDef.type = rb.m_mode == PBody2DComponent::Mode::dynamic ?
			b2_dynamicBody : b2_staticBody;
		
		//bodyDef.type = b2_dynamicBody; //TEMP
		
		bodyDef.position.Set(transform.GetPosition().x, transform.GetPosition().y);
		bodyDef.angle = glm::eulerAngles(transform.GetRotation()).z;
		bodyDef.gravityScale = rb.m_gScale;

		//bodyDef.gravityScale = 0; //TEMP

		if (rb.m_body->data != nullptr) //CLEAN
			m_world->DestroyBody(rb.m_body->data);
		
		rb.m_body->data = m_world->CreateBody(&bodyDef);
		
		switch (rb.m_shape)
		{
			case PBody2DComponent::Shape::circle:
				vec3 pos = transform.GetPosition();
				rb.m_circle.m_p.Set(pos.x, pos.y + -1.f);
				rb.m_circle.m_radius = rb.m_radius;			
				break;

			default: //Shape::box:
				rb.m_box.SetAsBox((rb.m_colliderSize.x / 2.f) * transform.GetScale().x,
					(rb.m_colliderSize.y / 2.f) * transform.GetScale().y);		
				break;
		}

		rb.m_bodyUpdated = true;
		UpdateFixture(entity);
	}

	Physic2DSystem::Physic2DSystem(Scene* scene)
		: m_scene(scene)
	{
		m_world = MakeRef<b2World>(b2Vec2(m_worldGravity.x, m_worldGravity.y));
	}

	void Physic2DSystem::Handle2dPhysics()
	{
		auto view = m_scene->registry.view<PBody2DComponent, TransformComponent>();
		auto& camera = m_scene->GetMainCamera().GetComponent<CameraComponent>();
		auto& cameraTransform = m_scene->GetMainCamera().GetComponent<TransformComponent>();

		m_world->Step(1.f / m_frameRate, m_velocityIterations, m_positionIterations);

		for (auto entity : view)
		{
			auto& rb = view.get<PBody2DComponent>(entity);

			if (!rb.enabled)
				continue;

			auto& transform = view.get<TransformComponent>(entity);

			//Apply physics to transforms
			b2Vec2 position = rb.m_body->data->GetPosition();
			transform.SetPosition({ position.x, position.y, transform.GetPosition().z });
			
			float angle = rb.m_body->data->GetAngle();
			float selfAngle = glm::eulerAngles(transform.GetRotation()).z;
			
			float dif = std::abs(std::abs(angle) - std::abs(selfAngle));

			if (dif > m_rotationOffset)
				transform.RotateGlobal(angle, VEC3_FORWARD);
		}
	}
}