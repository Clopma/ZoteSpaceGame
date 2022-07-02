#pragma once

#include "Rendering/Mesh.h"

#include "Utils/Math.h"
#include "Utils/Memory.h"
#include "Utils/GlobalStrings.h"

namespace Zote
{
	struct CircleGizmos
	{
	public:

		CircleGizmos()
		{
			//Quad data...
			float vertices[] = {
				// x	 y	 
				-0.5f, -0.5f, // 0
				 0.5f, -0.5f, // 1
				 0.5f,  0.5f, // 2
				-0.5f,	0.5f, // 3 
			};
			unsigned int indices[] = {
				0, 1, 2, //triangle 1
				2, 3, 0  //triangle 2
			};

			m_shader = MakeRef<Shader>(SHADER_VERT_CIRCLE, SHADER_FRAG_CIRCLE);
			m_mesh = MakeRef<Mesh>(ZOTE_2D_MESH, false, vertices, indices, 8, 6);
		}

		void Render(mat4 p, mat4 v, mat4 m)
		{
			Renderer::SetUniformVec3(UNIFORM_RESOLUTION, m_shader, vec3(800.f, 600.f, 0.f));
			Renderer::SetUniformColor(UNIFORM_CIRCLE_COLOR, m_shader, m_color);
			Renderer::SetUniformFloat(UNIFORM_CIRCLE_THICKNESS, m_shader, m_thickness);
			Renderer::SetUniformFloat(UNIFORM_CIRCLE_FADE, m_shader, m_fade);
			//setear los uniforms del renderer
			m_mesh->Render(m_shader, p, v, m);
		}

	private:
		Ref<Mesh> m_mesh;
		Ref<Shader> m_shader;

		Color m_color = Color::green;
		float m_thickness = 0.5f;
		float m_fade = 0.005f;
	};
}