#pragma once

#include "Rendering/Shader.h"
#include "Rendering/Line.h"

#include <vector>
#include <entt.hpp>

#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Zote
{
	struct BoxGizmo
	{
	public:

		entt::entity m_Entity;

		BoxGizmo(vec2 size, entt::entity entity)
			: m_Entity(entity)
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

	class Scene;

	class Box2DGizmoSystem
	{
	public:
		Box2DGizmoSystem(Scene* scene);
		void HandleBox2DGizmos();

	private:

		Scene* m_Scene;
		std::vector<BoxGizmo> m_BoxGizmos;

		BoxGizmo* FindGizmo(const entt::entity& entity);
	};
}


