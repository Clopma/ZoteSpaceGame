#pragma once

#include <entt.hpp>
#include <vector>

#include "ECS/Components/TransformComponent.h"

#include "Rendering/Line.h"

#include "Utils/Memory.h"
#include "Utils/Math.h"

namespace Zote
{
	class Scene;

	struct GizmosAxis
	{
		entt::entity m_entity;

		Ref<Line> m_forwardLine;
		Ref<Line> m_rightLine;
		Ref<Line> m_upLine;

		Ref<Shader> m_shader;

		const float m_lenght = .5f;

		void DrawGizmosAxis(mat4 p, mat4 v, mat4 m)
		{
			m_forwardLine->Render(m_shader, p, v, m);
			m_rightLine->Render(m_shader, p, v, m);
			m_upLine->Render(m_shader, p, v, m);
		}

		GizmosAxis(entt::entity entity)
			: m_entity(entity) 
		{
			m_shader = MakeRef<Shader>(SHADER_VERT_LINE, SHADER_FRAG_LINE);

			m_forwardLine = MakeRef<Line>(vec3(0, 0, 0), vec3(0, 0, 1) * m_lenght, Color::blue);
			m_rightLine = MakeRef<Line>(vec3(0, 0, 0), vec3(1, 0, 0) * m_lenght, Color::red);
			m_upLine = MakeRef<Line>(vec3(0, 0, 0), vec3(0, 1, 0) * m_lenght, Color::green);
		}
	};

	class GizmosAxisSystem
	{
	public:
		GizmosAxisSystem(Scene* scene);
		void HandleGizmosAxis();

	private:

		Scene* m_scene = nullptr;
		std::vector<GizmosAxis> gizmos;

		bool GizmosExists(const entt::entity& entity) const;

		void DrawGizmosAxis(const entt::entity& entity, mat4 p, mat4 v, mat4 m) const;
	};

	
}