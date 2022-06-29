#pragma once

#include "Core.h"
#include "BaseComponent.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

#include "Rendering/Line.h"

#include "Utils/Math.h"
#include "Utils/Memory.h"
#include "Utils/GlobalStrings.h"

namespace Zote
{
	struct BoxGizmos
	{
	public:
		BoxGizmos(vec2 size)
		{
			vec3 a = { -size.x / 2, size.y / 2, 0 };
			vec3 b = { size.x / 2, size.y / 2, 0 };
			vec3 c = { size.x / 2, -size.y / 2, 0 };
			vec3 d = { -size.x / 2, -size.y / 2, 0 };

			m_lineTop = MakeRef<Line>(a, b, m_color);
			m_LineRight = MakeRef<Line>(b, c, m_color);
			m_LineLeft = MakeRef<Line>(c, d, m_color);
			m_LineBottom = MakeRef<Line>(d, a, m_color);

			m_shader = MakeRef<Shader>(SHADER_VERT_LINE, SHADER_FRAG_LINE);
		}
		void Render(mat4 p, mat4 v, mat4 m)
		{
			m_lineTop->Render(m_shader, p, v, m);
			m_LineRight->Render(m_shader, p, v, m);
			m_LineLeft->Render(m_shader, p, v, m);
			m_LineBottom->Render(m_shader, p, v, m);
		}

	private:
		Ref<Line> m_lineTop;
		Ref<Line> m_LineRight;
		Ref<Line> m_LineLeft;
		Ref<Line> m_LineBottom;

		Ref<Shader> m_shader;
		const Color m_color = Color::green;
	};

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
		bool IsTrigger() const { return m_isTrigger; }

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
		void SetIsTrigger(bool isTrigger) 
		{
			if (m_isTrigger == isTrigger)
				return;
			m_isTrigger = isTrigger;
			m_fixtureUpdated = false;
		}

	private:

		Mode m_mode = Mode::kinematic;
		float m_gScale = 1.f;
		vec2 m_colliderSize = { 1.f, 1.f };
		float m_density = 1.f;
		float m_friction = .3f;
		bool m_isTrigger = false;
		
		bool m_bodyUpdated = false;
		bool m_fixtureUpdated = false;
		bool m_HasGizmos = false;

		b2Body* m_body = nullptr;
		b2Fixture* m_fixture = nullptr;
		
		b2PolygonShape m_box;
		Ref<BoxGizmos> boxGizmos;
	};
}
